#ifndef TMPYL_ABS_METHOD_H
#define TMPYL_ABS_METHOD_H

#define TMPYL_ABS_METHOD                                                       \
{                                                                              \
    "abs",                                                                     \
    tmpyl_abs,                                                                 \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.abs\n\r\t"                                                          \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the absolute value of the input."                                 \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for |x|. Allowed inputs are int,\n\r\t\t\t"          \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "abs_x:\n\r\t\t\t"                                                         \
    "The absolute value as a function of x. Same type as input.\n\r\t"         \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.abs(x)"                                                     \
}

#endif
