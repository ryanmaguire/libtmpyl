#ifndef TMPYL_FRESNEL_SIN_METHOD_H
#define TMPYL_FRESNEL_SIN_METHOD_H

#define TMPYL_FRESNEL_SIN_METHOD                                               \
{                                                                              \
    "fresnel_sin",                                                             \
    tmpyl_fresnel_sin,                                                         \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.fresnel_sin\n\r\t"                                                  \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the Fresnel Sine function, S(x)."                                 \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for S(x). Allowed inputs are int,\n\r\t\t\t"         \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "S_x:\n\r\t\t\t"                                                           \
    "The Fresnel Sine as a function of x. Same type as input.\n\r\t"           \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.fresnel_sin(x)"                                             \
}

#endif
