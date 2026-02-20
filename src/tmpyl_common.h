#ifndef TMPYL_COMMON_H
#define TMPYL_COMMON_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <libtmpl/include/tmpl.h>

typedef struct tmpyl_GenericFunctionObj_Def {

    /*  Integer valued functions.                                             */
    tmpl_LongFunction l2l;

    /*  Real valued functions that take real arguments.                       */
    tmpl_FloatFunction f2f;
    tmpl_DoubleFunction d2d;
    tmpl_LongDoubleFunction ld2ld;

    /*  Real valued functions that take complex arguments.                    */
    tmpl_ComplexFloatFunctional cf2f;
    tmpl_ComplexDoubleFunctional cd2d;
    tmpl_ComplexLongDoubleFunctional cld2ld;

    /*  Complex valued functions that take real arguments.                    */
    tmpl_ComplexDoublePath d2cd;
    tmpl_ComplexFloatPath f2cf;
    tmpl_ComplexLongDoublePath ld2cld;

    /*  Complex valued functions that take complex arguments.                 */
    tmpl_ComplexFloatFunction cf2cf;
    tmpl_ComplexDoubleFunction cd2cd;
    tmpl_ComplexLongDoubleFunction cld2cld;

    /*  The name of the function.                                             */
    const char *func_name;

} tmpyl_GenericFunctionObj;

typedef struct tmpyl_WindowObj_Def {

    /*  Real valued windows that take real arguments.                         */
    tmpl_WindowFunctionFloat fwindow;
    tmpl_WindowFunctionDouble dwindow;
    tmpl_WindowFunctionLongDouble ldwindow;

    /*  The name of the function.                                             */
    const char *func_name;

} tmpyl_WindowObj;

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self,
                        PyObject *args,
                        const tmpyl_GenericFunctionObj * const cfuncs);

extern PyObject *
tmpyl_window_wrapper(PyObject *self,
                     PyObject *args,
                     const tmpyl_WindowObj * const wfuncs);
#endif
