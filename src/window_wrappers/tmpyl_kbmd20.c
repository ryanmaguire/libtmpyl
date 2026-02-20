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
#include "../tmpyl_common.h"
#include "../tmpyl_window_wrappers.h"
#include <libtmpl/include/tmpl_window_functions.h>

/*  Python wrapper for the kbmd20 function from libtmpl.                      */
PyObject *tmpyl_kbmd20(PyObject *self, PyObject *args)
{
    /*  Function object that will contain all of the function pointers.       */
    tmpyl_WindowObj w_funcs;

    /*  Real valued windows that take real arguments.                         */
    w_funcs.fwindow = tmpl_Float_KBMD20;
    w_funcs.dwindow = tmpl_Double_KBMD20;
    w_funcs.ldwindow = tmpl_LDouble_KBMD20;

    /*  Name of the function.                                                 */
    w_funcs.func_name = "kbmd20";

    return tmpyl_window_wrapper(self, args, &w_funcs);
}
/*  End of tmpyl_kbmd20.                                                      */
