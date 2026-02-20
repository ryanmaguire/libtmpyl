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
 ******************************************************************************
 *                            tmpyl_window_methods                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the "methods" for the libtmpl functions, which allow them to *
 *      be called from Python.                                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the Python-C API.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 20, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPYL_WINDOW_METHODS_H
#define TMPYL_WINDOW_METHODS_H

/*  The Python-C API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*  Methods for all of the libtmpl functions.                                 */
#include "window_methods/tmpyl_kbmd20_method.h"

#endif
/*  End of include guard.                                                     */
