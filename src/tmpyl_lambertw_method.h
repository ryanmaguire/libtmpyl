#ifndef TMPYL_LAMBERTW_METHOD_H
#define TMPYL_LAMBERTW_METHOD_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "tmpyl_common.h"

#define TMPYL_LAMBERTW_METHOD                                                  \
{                                                                              \
    "lambertw",                                                                \
    tmpyl_lambertw,                                                            \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.lambertw\n\r\t"                                                     \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the Lambert W function, the inverse of f(x) = x*exp(x)."          \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for W(x). Allowed inputs are int,\n\r\t\t\t"         \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "C_x:\n\r\t\t\t"                                                           \
    "The Lambert W function as a function of x. Same type as input.\n\r\t"     \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.lambertw(x)"                                                \
}


#endif
