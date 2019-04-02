/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(dict_fromkeys__doc__,
"fromkeys($type, __iterable, __value=None)\n"
"--\n"
"\n"
"Create a new dictionary with keys from iterable and values set to value.");

#define DICT_FROMKEYS_METHODDEF    \
    {"fromkeys", (PyCFunction)(void(*)(void))dict_fromkeys, METH_FASTCALL|METH_CLASS, dict_fromkeys__doc__},

static PyObject *
dict_fromkeys_impl(PyTypeObject *type, PyObject *iterable, PyObject *value);

static PyObject *
dict_fromkeys(PyTypeObject *type, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *iterable;
    PyObject *value = Py_None;

    if (!_PyArg_CheckPositional("fromkeys", nargs, 1, 2)) {
        goto exit;
    }
    iterable = args[0];
    if (nargs < 2) {
        goto skip_optional;
    }
    value = args[1];
skip_optional:
    return_value = dict_fromkeys_impl(type, iterable, value);

exit:
    return return_value;
}

PyDoc_STRVAR(dict___contains____doc__,
"__contains__($self, __key)\n"
"--\n"
"\n"
"True if the dictionary has the specified key, else False.");

#define DICT___CONTAINS___METHODDEF    \
    {"__contains__", (PyCFunction)dict___contains__, METH_O|METH_COEXIST, dict___contains____doc__},

PyDoc_STRVAR(dict_get__doc__,
"get($self, __key, __default=None)\n"
"--\n"
"\n"
"Return the value for key if key is in the dictionary, else default.");

#define DICT_GET_METHODDEF    \
    {"get", (PyCFunction)(void(*)(void))dict_get, METH_FASTCALL, dict_get__doc__},

static PyObject *
dict_get_impl(PyDictObject *self, PyObject *key, PyObject *default_value);

static PyObject *
dict_get(PyDictObject *self, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *key;
    PyObject *default_value = Py_None;

    if (!_PyArg_CheckPositional("get", nargs, 1, 2)) {
        goto exit;
    }
    key = args[0];
    if (nargs < 2) {
        goto skip_optional;
    }
    default_value = args[1];
skip_optional:
    return_value = dict_get_impl(self, key, default_value);

exit:
    return return_value;
}

PyDoc_STRVAR(dict_setdefault__doc__,
"setdefault($self, __key, __default=None)\n"
"--\n"
"\n"
"Insert key with a value of default if key is not in the dictionary.\n"
"\n"
"Return the value for key if key is in the dictionary, else default.");

#define DICT_SETDEFAULT_METHODDEF    \
    {"setdefault", (PyCFunction)(void(*)(void))dict_setdefault, METH_FASTCALL, dict_setdefault__doc__},

static PyObject *
dict_setdefault_impl(PyDictObject *self, PyObject *key,
                     PyObject *default_value);

static PyObject *
dict_setdefault(PyDictObject *self, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *key;
    PyObject *default_value = Py_None;

    if (!_PyArg_CheckPositional("setdefault", nargs, 1, 2)) {
        goto exit;
    }
    key = args[0];
    if (nargs < 2) {
        goto skip_optional;
    }
    default_value = args[1];
skip_optional:
    return_value = dict_setdefault_impl(self, key, default_value);

exit:
    return return_value;
}

PyDoc_STRVAR(dict___reversed____doc__,
"__reversed__($self)\n"
"--\n"
"\n"
"Return a reverse iterator over the dict keys.");

#define DICT___REVERSED___METHODDEF    \
    {"__reversed__", (PyCFunction)dict___reversed__, METH_NOARGS, dict___reversed____doc__},

static PyObject *
dict___reversed___impl(PyDictObject *self);

static PyObject *
dict___reversed__(PyDictObject *self, PyObject *Py_UNUSED(ignored))
{
    return dict___reversed___impl(self);
}
/*[clinic end generated code: output=a47b8c97edab6988 input=a9049054013a1b77]*/
