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

/*  Python wrapper for the sqrt function from libtmpl.                        */
PyObject *tmpyl_sqrt(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpyl_GenericFunctionObj c_funcs;

    /*  Integer valued functions.                                             */
    c_funcs.l2l = NULL;

    /*  Real valued functions that take real arguments.                       */
    c_funcs.f2f = tmpl_Float_Sqrt;
    c_funcs.d2d = tmpl_Double_Sqrt;
    c_funcs.ld2ld = tmpl_LDouble_Sqrt;

    /*  Real valued functions that take complex arguments.                    */
    c_funcs.cf2f = NULL;
    c_funcs.cd2d = NULL;
    c_funcs.cld2ld = NULL;

    /*  Complex valued functions that take real arguments.                    */
    c_funcs.f2cf = NULL;
    c_funcs.d2cd = NULL;
    c_funcs.ld2cld = NULL;

    /*  Complex valued functions that take complex arguments.                 */
    c_funcs.cf2cf = NULL;
    c_funcs.cd2cd = NULL;
    c_funcs.cld2cld = NULL;

    /*  Name of the function.                                                 */
    c_funcs.func_name = "sqrt";

    return tmpl_Get_Py_Func_From_C(self, args, &c_funcs);
}
/*  End of tmpyl_sqrt.                                                        */
