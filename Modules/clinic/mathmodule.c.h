/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(math_gcd__doc__,
"gcd($module, __x, __y)\n"
"--\n"
"\n"
"greatest common divisor of x and y");

#define MATH_GCD_METHODDEF    \
    {"gcd", (PyCFunction)(void(*)(void))math_gcd, METH_FASTCALL, math_gcd__doc__},

static PyObject *
math_gcd_impl(PyObject *module, PyObject *a, PyObject *b);

static PyObject *
math_gcd(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *a;
    PyObject *b;

    if (!_PyArg_CheckPositional("gcd", nargs, 2, 2)) {
        goto exit;
    }
    a = args[0];
    b = args[1];
    return_value = math_gcd_impl(module, a, b);

exit:
    return return_value;
}

PyDoc_STRVAR(math_ceil__doc__,
"ceil($module, __x)\n"
"--\n"
"\n"
"Return the ceiling of x as an Integral.\n"
"\n"
"This is the smallest integer >= x.");

#define MATH_CEIL_METHODDEF    \
    {"ceil", (PyCFunction)math_ceil, METH_O, math_ceil__doc__},

PyDoc_STRVAR(math_floor__doc__,
"floor($module, __x)\n"
"--\n"
"\n"
"Return the floor of x as an Integral.\n"
"\n"
"This is the largest integer <= x.");

#define MATH_FLOOR_METHODDEF    \
    {"floor", (PyCFunction)math_floor, METH_O, math_floor__doc__},

PyDoc_STRVAR(math_fsum__doc__,
"fsum($module, __seq)\n"
"--\n"
"\n"
"Return an accurate floating point sum of values in the iterable seq.\n"
"\n"
"Assumes IEEE-754 floating point arithmetic.");

#define MATH_FSUM_METHODDEF    \
    {"fsum", (PyCFunction)math_fsum, METH_O, math_fsum__doc__},

PyDoc_STRVAR(math_factorial__doc__,
"factorial($module, __x)\n"
"--\n"
"\n"
"Find x!.\n"
"\n"
"Raise a ValueError if x is negative or non-integral.");

#define MATH_FACTORIAL_METHODDEF    \
    {"factorial", (PyCFunction)math_factorial, METH_O, math_factorial__doc__},

PyDoc_STRVAR(math_trunc__doc__,
"trunc($module, __x)\n"
"--\n"
"\n"
"Truncates the Real x to the nearest Integral toward 0.\n"
"\n"
"Uses the __trunc__ magic method.");

#define MATH_TRUNC_METHODDEF    \
    {"trunc", (PyCFunction)math_trunc, METH_O, math_trunc__doc__},

PyDoc_STRVAR(math_frexp__doc__,
"frexp($module, __x)\n"
"--\n"
"\n"
"Return the mantissa and exponent of x, as pair (m, e).\n"
"\n"
"m is a float and e is an int, such that x = m * 2.**e.\n"
"If x is 0, m and e are both 0.  Else 0.5 <= abs(m) < 1.0.");

#define MATH_FREXP_METHODDEF    \
    {"frexp", (PyCFunction)math_frexp, METH_O, math_frexp__doc__},

static PyObject *
math_frexp_impl(PyObject *module, double x);

static PyObject *
math_frexp(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_frexp_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_ldexp__doc__,
"ldexp($module, __x, __i)\n"
"--\n"
"\n"
"Return x * (2**i).\n"
"\n"
"This is essentially the inverse of frexp().");

#define MATH_LDEXP_METHODDEF    \
    {"ldexp", (PyCFunction)(void(*)(void))math_ldexp, METH_FASTCALL, math_ldexp__doc__},

static PyObject *
math_ldexp_impl(PyObject *module, double x, PyObject *i);

static PyObject *
math_ldexp(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    double x;
    PyObject *i;

    if (!_PyArg_CheckPositional("ldexp", nargs, 2, 2)) {
        goto exit;
    }
    x = PyFloat_AsDouble(args[0]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    i = args[1];
    return_value = math_ldexp_impl(module, x, i);

exit:
    return return_value;
}

PyDoc_STRVAR(math_modf__doc__,
"modf($module, __x)\n"
"--\n"
"\n"
"Return the fractional and integer parts of x.\n"
"\n"
"Both results carry the sign of x and are floats.");

#define MATH_MODF_METHODDEF    \
    {"modf", (PyCFunction)math_modf, METH_O, math_modf__doc__},

static PyObject *
math_modf_impl(PyObject *module, double x);

static PyObject *
math_modf(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_modf_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_log__doc__,
"log(x, [base=math.e])\n"
"Return the logarithm of x to the given base.\n"
"\n"
"If the base not specified, returns the natural logarithm (base e) of x.");

#define MATH_LOG_METHODDEF    \
    {"log", (PyCFunction)math_log, METH_VARARGS, math_log__doc__},

static PyObject *
math_log_impl(PyObject *module, PyObject *x, int group_right_1,
              PyObject *base);

static PyObject *
math_log(PyObject *module, PyObject *args)
{
    PyObject *return_value = NULL;
    PyObject *x;
    int group_right_1 = 0;
    PyObject *base = NULL;

    switch (PyTuple_GET_SIZE(args)) {
        case 1:
            if (!PyArg_ParseTuple(args, "O:log", &x)) {
                goto exit;
            }
            break;
        case 2:
            if (!PyArg_ParseTuple(args, "OO:log", &x, &base)) {
                goto exit;
            }
            group_right_1 = 1;
            break;
        default:
            PyErr_SetString(PyExc_TypeError, "math.log requires 1 to 2 arguments");
            goto exit;
    }
    return_value = math_log_impl(module, x, group_right_1, base);

exit:
    return return_value;
}

PyDoc_STRVAR(math_log2__doc__,
"log2($module, __x)\n"
"--\n"
"\n"
"Return the base 2 logarithm of x.");

#define MATH_LOG2_METHODDEF    \
    {"log2", (PyCFunction)math_log2, METH_O, math_log2__doc__},

PyDoc_STRVAR(math_log10__doc__,
"log10($module, __x)\n"
"--\n"
"\n"
"Return the base 10 logarithm of x.");

#define MATH_LOG10_METHODDEF    \
    {"log10", (PyCFunction)math_log10, METH_O, math_log10__doc__},

PyDoc_STRVAR(math_fmod__doc__,
"fmod($module, __x, __y)\n"
"--\n"
"\n"
"Return fmod(x, y), according to platform C.\n"
"\n"
"x % y may differ.");

#define MATH_FMOD_METHODDEF    \
    {"fmod", (PyCFunction)(void(*)(void))math_fmod, METH_FASTCALL, math_fmod__doc__},

static PyObject *
math_fmod_impl(PyObject *module, double x, double y);

static PyObject *
math_fmod(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    double x;
    double y;

    if (!_PyArg_CheckPositional("fmod", nargs, 2, 2)) {
        goto exit;
    }
    x = PyFloat_AsDouble(args[0]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    y = PyFloat_AsDouble(args[1]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_fmod_impl(module, x, y);

exit:
    return return_value;
}

PyDoc_STRVAR(math_dist__doc__,
"dist($module, __p, __q)\n"
"--\n"
"\n"
"Return the Euclidean distance between two points p and q.\n"
"\n"
"The points should be specified as tuples of coordinates.\n"
"Both tuples must be the same size.\n"
"\n"
"Roughly equivalent to:\n"
"    sqrt(sum((px - qx) ** 2.0 for px, qx in zip(p, q)))");

#define MATH_DIST_METHODDEF    \
    {"dist", (PyCFunction)(void(*)(void))math_dist, METH_FASTCALL, math_dist__doc__},

static PyObject *
math_dist_impl(PyObject *module, PyObject *p, PyObject *q);

static PyObject *
math_dist(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    PyObject *p;
    PyObject *q;

    if (!_PyArg_CheckPositional("dist", nargs, 2, 2)) {
        goto exit;
    }
    if (!PyTuple_Check(args[0])) {
        _PyArg_BadArgument("dist", 1, "tuple", args[0]);
        goto exit;
    }
    p = args[0];
    if (!PyTuple_Check(args[1])) {
        _PyArg_BadArgument("dist", 2, "tuple", args[1]);
        goto exit;
    }
    q = args[1];
    return_value = math_dist_impl(module, p, q);

exit:
    return return_value;
}

PyDoc_STRVAR(math_pow__doc__,
"pow($module, __x, __y)\n"
"--\n"
"\n"
"Return x**y (x to the power of y).");

#define MATH_POW_METHODDEF    \
    {"pow", (PyCFunction)(void(*)(void))math_pow, METH_FASTCALL, math_pow__doc__},

static PyObject *
math_pow_impl(PyObject *module, double x, double y);

static PyObject *
math_pow(PyObject *module, PyObject *const *args, Py_ssize_t nargs)
{
    PyObject *return_value = NULL;
    double x;
    double y;

    if (!_PyArg_CheckPositional("pow", nargs, 2, 2)) {
        goto exit;
    }
    x = PyFloat_AsDouble(args[0]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    y = PyFloat_AsDouble(args[1]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_pow_impl(module, x, y);

exit:
    return return_value;
}

PyDoc_STRVAR(math_degrees__doc__,
"degrees($module, __x)\n"
"--\n"
"\n"
"Convert angle x from radians to degrees.");

#define MATH_DEGREES_METHODDEF    \
    {"degrees", (PyCFunction)math_degrees, METH_O, math_degrees__doc__},

static PyObject *
math_degrees_impl(PyObject *module, double x);

static PyObject *
math_degrees(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_degrees_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_radians__doc__,
"radians($module, __x)\n"
"--\n"
"\n"
"Convert angle x from degrees to radians.");

#define MATH_RADIANS_METHODDEF    \
    {"radians", (PyCFunction)math_radians, METH_O, math_radians__doc__},

static PyObject *
math_radians_impl(PyObject *module, double x);

static PyObject *
math_radians(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_radians_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_isfinite__doc__,
"isfinite($module, __x)\n"
"--\n"
"\n"
"Return True if x is neither an infinity nor a NaN, and False otherwise.");

#define MATH_ISFINITE_METHODDEF    \
    {"isfinite", (PyCFunction)math_isfinite, METH_O, math_isfinite__doc__},

static PyObject *
math_isfinite_impl(PyObject *module, double x);

static PyObject *
math_isfinite(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_isfinite_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_isnan__doc__,
"isnan($module, __x)\n"
"--\n"
"\n"
"Return True if x is a NaN (not a number), and False otherwise.");

#define MATH_ISNAN_METHODDEF    \
    {"isnan", (PyCFunction)math_isnan, METH_O, math_isnan__doc__},

static PyObject *
math_isnan_impl(PyObject *module, double x);

static PyObject *
math_isnan(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_isnan_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_isinf__doc__,
"isinf($module, __x)\n"
"--\n"
"\n"
"Return True if x is a positive or negative infinity, and False otherwise.");

#define MATH_ISINF_METHODDEF    \
    {"isinf", (PyCFunction)math_isinf, METH_O, math_isinf__doc__},

static PyObject *
math_isinf_impl(PyObject *module, double x);

static PyObject *
math_isinf(PyObject *module, PyObject *arg)
{
    PyObject *return_value = NULL;
    double x;

    x = PyFloat_AsDouble(arg);
    if (PyErr_Occurred()) {
        goto exit;
    }
    return_value = math_isinf_impl(module, x);

exit:
    return return_value;
}

PyDoc_STRVAR(math_isclose__doc__,
"isclose($module, a, b, *, rel_tol=1e-09, abs_tol=0.0)\n"
"--\n"
"\n"
"Determine whether two floating point numbers are close in value.\n"
"\n"
"  rel_tol\n"
"    maximum difference for being considered \"close\", relative to the\n"
"    magnitude of the input values\n"
"  abs_tol\n"
"    maximum difference for being considered \"close\", regardless of the\n"
"    magnitude of the input values\n"
"\n"
"Return True if a is close in value to b, and False otherwise.\n"
"\n"
"For the values to be considered close, the difference between them\n"
"must be smaller than at least one of the tolerances.\n"
"\n"
"-inf, inf and NaN behave similarly to the IEEE 754 Standard.  That\n"
"is, NaN is not close to anything, even itself.  inf and -inf are\n"
"only close to themselves.");

#define MATH_ISCLOSE_METHODDEF    \
    {"isclose", (PyCFunction)(void(*)(void))math_isclose, METH_FASTCALL|METH_KEYWORDS, math_isclose__doc__},

static int
math_isclose_impl(PyObject *module, double a, double b, double rel_tol,
                  double abs_tol);

static PyObject *
math_isclose(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"a", "b", "rel_tol", "abs_tol", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "isclose", 0};
    PyObject *argsbuf[4];
    Py_ssize_t noptargs = nargs + (kwnames ? PyTuple_GET_SIZE(kwnames) : 0) - 2;
    double a;
    double b;
    double rel_tol = 1e-09;
    double abs_tol = 0.0;
    int _return_value;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 2, 2, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    a = PyFloat_AsDouble(args[0]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    b = PyFloat_AsDouble(args[1]);
    if (PyErr_Occurred()) {
        goto exit;
    }
    if (!noptargs) {
        goto skip_optional_kwonly;
    }
    if (args[2]) {
        rel_tol = PyFloat_AsDouble(args[2]);
        if (PyErr_Occurred()) {
            goto exit;
        }
        if (!--noptargs) {
            goto skip_optional_kwonly;
        }
    }
    abs_tol = PyFloat_AsDouble(args[3]);
    if (PyErr_Occurred()) {
        goto exit;
    }
skip_optional_kwonly:
    _return_value = math_isclose_impl(module, a, b, rel_tol, abs_tol);
    if ((_return_value == -1) && PyErr_Occurred()) {
        goto exit;
    }
    return_value = PyBool_FromLong((long)_return_value);

exit:
    return return_value;
}

PyDoc_STRVAR(math_prod__doc__,
"prod($module, __iterable, *, start=1)\n"
"--\n"
"\n"
"Calculate the product of all the elements in the input iterable.\n"
"\n"
"The default start value for the product is 1.\n"
"\n"
"When the iterable is empty, return the start value.  This function is\n"
"intended specifically for use with numeric values and may reject\n"
"non-numeric types.");

#define MATH_PROD_METHODDEF    \
    {"prod", (PyCFunction)(void(*)(void))math_prod, METH_FASTCALL|METH_KEYWORDS, math_prod__doc__},

static PyObject *
math_prod_impl(PyObject *module, PyObject *iterable, PyObject *start);

static PyObject *
math_prod(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"", "start", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "prod", 0};
    PyObject *argsbuf[2];
    Py_ssize_t noptargs = nargs + (kwnames ? PyTuple_GET_SIZE(kwnames) : 0) - 1;
    PyObject *iterable;
    PyObject *start = NULL;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    iterable = args[0];
    if (!noptargs) {
        goto skip_optional_kwonly;
    }
    start = args[1];
skip_optional_kwonly:
    return_value = math_prod_impl(module, iterable, start);

exit:
    return return_value;
}
/*[clinic end generated code: output=6e71a2f2e6ae2028 input=a9049054013a1b77]*/
