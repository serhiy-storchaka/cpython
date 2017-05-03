#if STRINGLIB_IS_UNICODE
# error "ctype.h only compatible with byte-wise strings"
#endif

#include "bytes_methods.h"

#define PREDICATE(name)                                         \
static PyObject *                                               \
stringlib_##name(PyObject *self)                                \
{                                                               \
    Py_buffer view;                                             \
    PyObject *result;                                           \
    if (PyObject_GetBuffer(self, &view, PyBUF_SIMPLE) != 0)     \
        return NULL;                                            \
    result = _Py_bytes_##name(view.buf, view.len);              \
    PyBuffer_Release(&view);                                    \
    return result;                                              \
}

PREDICATE(isspace)
PREDICATE(isalpha)
PREDICATE(isalnum)
PREDICATE(isdigit)
PREDICATE(islower)
PREDICATE(isupper)
PREDICATE(istitle)

#undef PREDICATE

/* functions that return a new object partially translated by ctype funcs: */

#define TRANSFORMER(name)                                       \
static PyObject *                                               \
stringlib_##name(PyObject *self)                                \
{                                                               \
    Py_buffer view;                                             \
    PyObject *result;                                           \
    if (PyObject_GetBuffer(self, &view, PyBUF_SIMPLE) != 0)     \
        return NULL;                                            \
    result = STRINGLIB_NEW(NULL, view.len);                     \
    if (result)                                                 \
        _Py_bytes_##name(STRINGLIB_STR(result), view.buf, view.len);  \
    PyBuffer_Release(&view);                                    \
    return result;                                              \
}

TRANSFORMER(lower)
TRANSFORMER(upper)
TRANSFORMER(title)
TRANSFORMER(capitalize)
TRANSFORMER(swapcase)

#undef TRANSFORMER
