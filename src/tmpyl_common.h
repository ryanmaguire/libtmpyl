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

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self,
                        PyObject *args,
                        const tmpyl_GenericFunctionObj * const cfuncs);

/*  All function wrappers for libtmpl.                                        */
extern PyObject *tmpyl_abs(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos_maclaurin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos_pade(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos_rat_remez(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos_tail_end(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin_maclaurin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin_pade(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin_rat_remez(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin_tail_end(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan_pade(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan_maclaurin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselI0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cbrt(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cosd(PyObject *self, PyObject *args);
extern PyObject *tmpyl_erf(PyObject *self, PyObject *args);
extern PyObject *tmpyl_exp(PyObject *self, PyObject *args);
extern PyObject *tmpyl_floor(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_lambertw(PyObject *self, PyObject *args);
extern PyObject *tmpyl_log(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_2(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_360(PyObject *self, PyObject *args);
extern PyObject *tmpyl_normalized_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_normalized_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinc(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sincpi(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinpi(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sind(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sqrt(PyObject *self, PyObject *args);
extern PyObject *tmpyl_trunc(PyObject *self, PyObject *args);

#endif
