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
 *                           tmpyl_window_wrappers                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the "wrappers" for Python that call the C routines.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the C-Python API.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 20, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPYL_WINDOW_WRAPPERS_H
#define TMPYL_WINDOW_WRAPPERS_H

/*  The C-Python API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*  All window function wrappers for libtmpl.                                 */
extern PyObject *tmpyl_kbmd20(PyObject *self, PyObject *args);

#endif
/*  End of include guard.                                                     */
