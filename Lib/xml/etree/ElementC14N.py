#
# ElementTree
# $Id: ElementC14N.py 3440 2008-07-18 14:45:01Z fredrik $
#
# canonicalisation (c14n) support for element trees.
#
# history:
# 2007-12-14 fl   created (normalized version)
# 2008-02-12 fl   roundtrip support
# 2008-03-03 fl   fixed parent map and scope setting/sorting bugs
# 2008-03-05 fl   fixed namespace declarations in exclusive mode
# 2008-03-10 fl   added inclusive subset support
# 2008-03-12 fl   fixed scope import in inclusive subset mode
# 2008-06-13 fl   add support for explicitly scoped trees
# 2008-07-18 fl   fixed duplicate declaration in exclusive serializer
#
# Copyright (c) 2007-2008 by Fredrik Lundh.  All rights reserved.
#
# fredrik@pythonware.com
# http://www.pythonware.com
#
# --------------------------------------------------------------------
# The ElementTree toolkit is
#
# Copyright (c) 1999-2008 by Fredrik Lundh
#
# By obtaining, using, and/or copying this software and/or its
# associated documentation, you agree that you have read, understood,
# and will comply with the following terms and conditions:
#
# Permission to use, copy, modify, and distribute this software and
# its associated documentation for any purpose and without fee is
# hereby granted, provided that the above copyright notice appears in
# all copies, and that both that copyright notice and this permission
# notice appear in supporting documentation, and that the name of
# Secret Labs AB or the author not be used in advertising or publicity
# pertaining to distribution of the software without specific, written
# prior permission.
#
# SECRET LABS AB AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
# TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANT-
# ABILITY AND FITNESS.  IN NO EVENT SHALL SECRET LABS AB OR THE AUTHOR
# BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
# DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
# ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.
# --------------------------------------------------------------------

from .ElementTree import QName
from .ElementTree import ElementTree, iterparse
from .ElementTree import _namespaces, _raise_serialization_error

# --------------------------------------------------------------------
# C14N escape methods

def _escape_cdata_c14n(text):
    # escape character data
    try:
        # it's worth avoiding do-nothing calls for strings that are
        # shorter than 500 character, or so.  assume that's, by far,
        # the most common case in most applications.
        if '&' in text:
            text = text.replace('&', '&amp;')
        if '<' in text:
            text = text.replace('<', '&lt;')
        if '>' in text:
            text = text.replace('>', '&gt;')
        if '\r' in text:
            text = text.replace('\n', '&#xD;')
        return text
    except (TypeError, AttributeError):
        _raise_serialization_error(text)

def _escape_attrib_c14n(text):
    # escape attribute value
    try:
        if '&' in text:
            text = text.replace('&', '&amp;')
        if '<' in text:
            text = text.replace('<', '&lt;')
        if '"' in text:
            text = text.replace('"', '&quot;')
        if '\t' in text:
            text = text.replace('\t', '&#x9;')
        if '\n' in text:
            text = text.replace('\n', '&#xA;')
        if '\r' in text:
            text = text.replace('\r', '&#xD;')
        return text
    except (TypeError, AttributeError):
        _raise_serialization_error(text)

# --------------------------------------------------------------------

class WriteC14N:
    # C14N writer target

    def __init__(self, write):
        self.write = write

    def start(self, tag, attrs):
        # expects to get the attributes as a list of pairs, *in order*
        # FIXME: pass in prefix/uri/tag triples instead?
        write = self.write
        write('<' + tag)
        for k, v in attrs:
            write(' %s="%s"' % (k, _escape_attrib_c14n(v)))
        write('>')

    def data(self, data):
        self.write(_escape_cdata_c14n(data))

    def end(self, tag):
        self.write('</' + tag + '>')

def _serialize(elem, target, qnames, namespaces):

    # event generator
    def emit(elem, namespaces=None):
        tag = qnames[elem.tag]
        attrib = []
        # namespaces first, sorted by prefix
        if namespaces:
            for v, k in sorted(namespaces.items(), key=lambda x: x[1]):
                attrib.append(('xmlns:' + k, v))
        # attributes next, sorted by (uri, local)
        for k, v in sorted(elem.attrib.items()):
            if k[:6] != 'xmlns:':
                attrib.append((qnames[k], v))
        target.start(tag, attrib)
        if elem.text:
            target.data(elem.text)
        for e in elem:
            emit(e)
        target.end(tag)
        if elem.tail:
            target.data(elem.tail)

    emit(elem, namespaces)

def _serialize_inclusive(elem, target, scope, parent, nsmap):

    def qname(elem, qname):
        if qname[:1] == '{':
            uri, tag = qname[1:].rsplit('}', 1)
            for prefix, u in _listscopes(elem, scope, parent):
                if u == uri:
                    break
            else:
                raise ValueError('%s not in scope' % uri) # FIXME
            if prefix == '':
                return tag # default namespace
            return prefix + ':' + tag
        else:
            return qname

    def emit(elem, nsmap):
        tag = qname(elem, elem.tag)
        attrib = []
        # namespaces first, sorted by prefix
        namespaces = scope.get(elem)
        if namespaces or nsmap:
            if not namespaces:
                namespaces = []
            if nsmap:
                nsdict = dict(namespaces)
                for p, u in nsmap:
                    if p not in nsdict:
                        namespaces.append((p, u))
            for p, u in sorted(namespaces):
                if p:
                    attrib.append(('xmlns:' + p, u))
        # attributes next, sorted by (uri, local)
        for k, v in sorted(elem.attrib.items()):
            if k[:6] != 'xmlns:':
                attrib.append((qname(elem, k), v))
        target.start(tag, attrib)
        if elem.text:
            target.data(elem.text)
        for e in elem:
            emit(e, None)
        target.end(tag)
        if elem.tail:
            target.data(elem.tail)

    emit(elem, nsmap)

def _serialize_exclusive(elem, target, scope, parent, nsmap, nsinclude):

    def qname(elem, qname):
        if qname[:1] == '{':
            uri, tag = qname[1:].rsplit('}', 1)
            for prefix, u in _listscopes(elem, scope, parent):
                if u == uri:
                    break
            else:
                raise ValueError('%s not in scope' % uri)
            return prefix, uri, prefix + ':' + tag
        else:
            return None, None, qname

    stack = [{}]

    def emit(elem, nsmap):
        # identify target namespaces
        namespaces = {}
        rendered = stack[-1].copy()
        # element tag
        prefix, uri, tag = qname(elem, elem.tag)
        if prefix:
            namespaces[prefix] = uri
        # attributes
        attrib = []
        for k, v in sorted(elem.attrib.items()):
            if k[:6] != 'xmlns:':
                prefix, uri, k = qname(elem, k)
                if prefix:
                    namespaces[prefix] = uri
                attrib.append((k, v))
        # explicitly included namespaces
        if nsinclude:
            if nsmap:
                for p, u in nsmap:
                    if p not in namespaces and p in nsinclude:
                        namespaces[p] = u
            if elem in scope:
                for p, u in scope[elem]:
                    if p not in namespaces and p in nsinclude:
                        namespaces[p] = u
        # build namespace attribute list
        xmlns = []
        for p, u in sorted(namespaces.items()):
            if p and rendered.get(p) != u:
                xmlns.append(('xmlns:' + p, u))
            rendered[p] = u
        # serialize
        target.start(tag, xmlns + attrib)
        if elem.text:
            target.data(elem.text)
        stack.append(rendered)
        for e in elem:
            emit(e, None)
        stack.pop()
        target.end(tag)
        if elem.tail:
            target.data(elem.tail)

    emit(elem, nsmap)

##
# (Internal) Hook used by ElementTree's c14n output method

def _serialize_c14n(write, elem, qnames, namespaces,
                    short_empty_elements, **kwargs):
    _serialize(elem, WriteC14N(write), qnames, namespaces)

##
# Writes a canonicalized document.  If used with {@link parse}, this can
# be used to create canonical versions of existing documents.
#
# @def write(elem, file, subset=None, **options)
# @param elem Element or ElementTree.  If passed a tree created by {@link
#     parse}, the function attempts to preserve existing prefixes.
#     Otherwise, new prefixes are allocated.
# @param file Output file.  Can be either a filename or a file-like object.
# @param subset Subset element, if applicable.
# @param **options Options, given as keyword arguments.
# @keyparam exclusive Use exclusive C14N.  In this mode, namespaces
#     declarations are moved to the first element (in document order)
#     that actually uses the namespace.
# @keyparam inclusive_namespaces If given, a list or set of prefxies
#     that should be retained in the serialized document, even if
#     they're not used.  This applies to exclusive serialization only
#     (for inclusive subsets, all prefixes are always included).

def write(elem, file_or_filename, subset=None,
          exclusive=False, inclusive_namespaces=None):
    if hasattr(file_or_filename, 'write'):
        file = file_or_filename
    else:
        file = open(file_or_filename, 'wb')
    out = WriteC14N(file.write)
    try:
        if not hasattr(elem, '_scope'):
            # ordinary tree; allocate new prefixes up front
            if subset is not None:
                raise ValueError('subset only works for scoped trees')
            qnames, namespaces = _namespaces(elem, 'utf-8')
            _serialize(elem.getroot(), out, qnames, namespaces)
            return

        # scoped tree
        scope = elem._scope
        parent = elem._parent

        if subset is not None:
            # get list of imported scopes
            nsmap = {}
            for p, u in _listscopes(subset, scope, parent):
                if p not in nsmap:
                    nsmap[p] = u
            nsmap = list(nsmap.items())
            elem = subset
        else:
            elem = elem.getroot()
            nsmap = []

        if exclusive:
            # exclusive mode
            nsinclude = set(inclusive_namespaces or ())
            _serialize_exclusive(elem, out, scope, parent, nsmap, nsinclude)
            return
        else:
            # inclusive mode
            _serialize_inclusive(elem, out, scope, parent, nsmap)

    finally:
        if file is not file_or_filename:
            file.close()

##
# Parses an XML file, and builds a tree annotated with scope and parent
# information.  To parse from a string, use the StringIO module.
#
# @param file A file name or file object.
# @return An extended ElementTree, with extra scope and parent information
#    attached to the ElementTree object.

def parse(file):

    events = 'start', 'start-ns', 'end'

    root = None
    ns_map = []

    scope = {}
    parent = {}

    stack = []

    for event, elem in iterparse(file, events):

        if event == 'start-ns':
            ns_map.append(elem)

        elif event == 'start':
            if stack:
                parent[elem] = stack[-1]
            stack.append(elem)
            if root is None:
                root = elem
            if ns_map:
                scope[elem] = ns_map
                ns_map = []

        elif event == 'end':
            stack.pop()

    tree = ElementTree(root)
    tree._scope = scope
    tree._parent = parent

    return tree

##
# (Helper) Takes an ElementTree with "xmlns" attributes and creates a
# scoped tree, for use with {@link write}.
#
# @param elem An element tree.
# @return A scoped tree, which can be passed to {@link write}.

def build_scoped_tree(elem):

    root = ElementTree(elem)

    # build scope map
    root._scope = {}
    for e in elem.iter():
        scope = []
        for k in e.keys():
            if k.startswith('xmlns:'):
                # move xmlns prefix to scope map
                scope.append((k[6:], e.get(k)))
                # del e.attrib[k]
        if scope:
            root._scope[e] = scope

    # build parent map
    root._parent = {c: p for p in elem.iter() for c in p}

    return root

##
# (Internal) Finds undefined URI:s in a scoped tree.

def _find_open_uris(elem, scope, parent):
    uris = {} # set of open URIs
    stack = [{}] # stack of namespace maps
    def qname(qname):
        if qname[:1] == '{':
            uri, tag = qname[1:].rsplit('}', 1)
            if uri not in stack[-1]:
                uris[uri] = None
    def check(elem):
        ns = stack[-1].copy()
        if elem in scope:
            for prefix, uri in scope[elem]:
                ns[uri] = prefix
        stack.append(ns)
        qname(elem.tag)
        for x in elem.keys():
            qname(x)
        for x in elem:
            check(x)
        stack.pop()
    check(elem)
    return list(uris.keys())

##
# (Internal) Returns a sequence of (prefix, uri) pairs.

def _listscopes(elem, scope, parent):
    while elem is not None:
        ns = scope.get(elem)
        if ns:
            yield from ns
        elem = parent.get(elem)

##
# (Internal) Finds prefix for given URI in a scoped tree.

def _findprefix(elem, scope, parent, uri):
    for p, u in _listscopes(elem, scope, parent):
        if u == uri:
            return p
    return None


