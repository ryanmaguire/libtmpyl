#ifndef TMPYL_FRESNEL_COS_METHOD_H
#define TMPYL_FRESNEL_COS_METHOD_H

#define TMPYL_FRESNEL_COS_METHOD                                               \
{                                                                              \
    "fresnel_cos",                                                             \
    tmpyl_fresnel_cos,                                                         \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.fresnel_cos\n\r\t"                                                  \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the Fresnel Cosine function, C(x)."                               \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for C(x). Allowed inputs are int,\n\r\t\t\t"         \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "C_x:\n\r\t\t\t"                                                           \
    "The Fresnel Cosine as a function of x. Same type as input.\n\r\t"         \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.fresnel_cos(x)"                                             \
}

#endif
