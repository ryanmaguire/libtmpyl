/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************/
#include "tmpyl_common.h"

/*  Python wrapper for the Fresnel Cos function from libtmpl.                 */
PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpyl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_Fresnel_Cos;
    c_funcs.double_func = tmpl_Double_Fresnel_Cos;
    c_funcs.ldouble_func = tmpl_LDouble_Fresnel_Cos;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.float_from_cfloat_func = NULL;
    c_funcs.double_from_cdouble_func = NULL;
    c_funcs.ldouble_from_cldouble_func = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.cfloat_from_float_func = NULL;
    c_funcs.cdouble_from_double_func = NULL;
    c_funcs.cldouble_from_ldouble_func = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cfloat_from_cfloat_func = NULL;
    c_funcs.cdouble_from_cdouble_func = NULL;
    c_funcs.cdouble_from_cldouble_func = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "fresnel_cos";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_fresnel_cos.                                                 */
