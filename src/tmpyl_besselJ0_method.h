#ifndef TMPYL_BESSELJ0_METHOD_H
#define TMPYL_BESSELJ0_METHOD_H

#define TMPYL_BESSELJ0_METHOD                                                  \
{                                                                              \
    "besselJ0",                                                                \
    tmpyl_besselJ0,                                                            \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.besselJ0\n\r\t"                                                     \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the Zeroth Bessel Function of the First Kind (J0)."               \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for J_0(x). Allowed inputs are int,\n\r\t\t\t"       \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "J0_x:\n\r\t\t\t"                                                          \
    "The Bessel Function J0 as a function of x. Same type as input.\n\r\t"     \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.besselJ0(x)"                                                \
}

#endif
