/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpyl.                                            *
 *                                                                            *
 *  libtmpyl is free software: you can redistribute it and/or modify it       *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpyl is distributed in the hope that it will be useful,               *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpyl.  If not, see <https://www.gnu.org/licenses/>.        *
 ******************************************************************************/
#include "tmpyl_common.h"

/*  Python wrapper for the Lambert W function from libtmpl.                   */
PyObject *tmpyl_lambertw(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpyl_Generic_Function_Obj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.long_func = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.float_func = tmpl_Float_LambertW;
    c_funcs.double_func = tmpl_Double_LambertW;
    c_funcs.ldouble_func = tmpl_LDouble_LambertW;

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
    c_funcs.func_name = "lambertw";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_lambertw.                                                    */
