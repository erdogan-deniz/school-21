#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <stdio.h>

double add(double a, double b) {
    return (a + b);
}

double sub(double a, double b) {
    return (a - b);
}

double mul(double a, double b) {
    return (a * b);
}

double diV(double a, double b) {
    if (b == 0) {
        printf("Traceback (most recent call last):\n");
        printf("ZeroDivisionError: Cannot divide by zero\n");
        exit(1);
    }

    return (a / b);
}

static PyObject* add_wrapper(PyObject* self, PyObject* args) {
    double a, b, result;

    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    result = add(a, b);

    if (result - (int)result > 0.00001)
        return PyFloat_FromDouble(result);
    else
        return PyLong_FromDouble(result);
}

static PyObject* sub_wrapper(PyObject* self, PyObject* args) {
    double a, b, result;

    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    result = sub(a, b);

    if (result - (int)result > 0.00001)
        return PyFloat_FromDouble(result);
    else
        return PyLong_FromDouble(result);
}

static PyObject* mul_wrapper(PyObject* self, PyObject* args) {
    double a, b, result;

    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    result = mul(a, b);

    if (result - (int)result > 0.00001)
        return PyFloat_FromDouble(result);
    else
        return PyLong_FromDouble(result);
}

static PyObject* div_wrapper(PyObject* self, PyObject* args) {

    double a, b, result;

    if (!PyArg_ParseTuple(args, "dd", &a, &b))
        return NULL;

    result = diV(a, b);

    if (result - (int)result > 0.00001)
        return PyFloat_FromDouble(result);
    else
        return PyLong_FromDouble(result);
}

static PyMethodDef module_methods[] = {
    {"add", add_wrapper, METH_VARARGS, "Calculate the sum of two digits."},
    {"sub", sub_wrapper, METH_VARARGS, "Calculate the difference of two digits."},
    {"mul", mul_wrapper, METH_VARARGS, "Calculate the multiplication of two digits."},
    {"diV", div_wrapper, METH_VARARGS, "Calculate the divison of two digits."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef calculator_module = {
    PyModuleDef_HEAD_INIT,
    "calculator",
    "A simple module to calculate simple number operations.",
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit_calculator(void) {
    return PyModule_Create(&calculator_module);
}
