#ifndef TMPYL_COMMON_H
#define TMPYL_COMMON_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <libtmpl/include/tmpl.h>

typedef struct _tmpyl_Generic_Function_Obj {
    /*  Integer valued functions.                                             */
    long (*long_func)(long);

    /*  Real valued functions that take real arguments.                       */
    float (*float_func)(float);
    double (*double_func)(double);
    long double (*ldouble_func)(long double);

    /*  Real valued functions that take complex arguments.                    */
    float (*float_from_cfloat_func)(tmpl_ComplexFloat);
    double (*double_from_cdouble_func)(tmpl_ComplexDouble);
    long double (*ldouble_from_cldouble_func)(tmpl_ComplexLongDouble);

    /*  Complex valued functions that take real arguments.                    */
    tmpl_ComplexFloat (*cfloat_from_float_func)(float);
    tmpl_ComplexDouble (*cdouble_from_double_func)(double);
    tmpl_ComplexLongDouble (*cldouble_from_ldouble_func)(long double);

    /*  Complex valued functions that take complex arguments.                 */
    tmpl_ComplexFloat (*cfloat_from_cfloat_func)(tmpl_ComplexFloat);
    tmpl_ComplexDouble (*cdouble_from_cdouble_func)(tmpl_ComplexDouble);
    tmpl_ComplexLongDouble
    (*cldouble_from_cldouble_func)(tmpl_ComplexLongDouble);

    /*  The name of the function.                                             */
    const char *func_name;
} tmpyl_Generic_Function_Obj;

extern PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self,
                        PyObject *args,
                        tmpyl_Generic_Function_Obj *c_func);

/*  All function wrappers for libtmpl.                                        */
extern PyObject *tmpyl_abs(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan_pade(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan_maclaurin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselI0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_besselJ0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cbrt(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cosd(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_lambertw(PyObject *self, PyObject *args);
extern PyObject *tmpyl_log(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_2(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_360(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinc(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sind(PyObject *self, PyObject *args);

#endif

