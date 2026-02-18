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
 *                               tmpyl_wrappers                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the "wrappers" for Python that call the C routines.          *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the C-Python API.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPYL_WRAPPERS_H
#define TMPYL_WRAPPERS_H

/*  The C-Python API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "tmpyl_common.h"


/*  All function wrappers for libtmpl.                                        */
extern PyObject *tmpyl_abs(PyObject *self, PyObject *args);
extern PyObject *tmpyl_acos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_asin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_atan(PyObject *self, PyObject *args);
extern PyObject *tmpyl_airy_j1(PyObject *self, PyObject *args);
extern PyObject *tmpyl_bessel_i0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_bessel_j0(PyObject *self, PyObject *args);
extern PyObject *tmpyl_bessel_j1(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cbrt(PyObject *self, PyObject *args);
extern PyObject *tmpyl_ceil(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cosd(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cosh(PyObject *self, PyObject *args);
extern PyObject *tmpyl_cospi(PyObject *self, PyObject *args);
extern PyObject *tmpyl_erf(PyObject *self, PyObject *args);
extern PyObject *tmpyl_exp(PyObject *self, PyObject *args);
extern PyObject *tmpyl_floor(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fractional_part(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_lambertw(PyObject *self, PyObject *args);
extern PyObject *tmpyl_log(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_2(PyObject *self, PyObject *args);
extern PyObject *tmpyl_mod_360(PyObject *self, PyObject *args);
extern PyObject *tmpyl_normalized_fresnel_cos(PyObject *self, PyObject *args);
extern PyObject *tmpyl_normalized_fresnel_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sin(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinc(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sincpi(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sind(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinh(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sinpi(PyObject *self, PyObject *args);
extern PyObject *tmpyl_sqrt(PyObject *self, PyObject *args);
extern PyObject *tmpyl_tan(PyObject *self, PyObject *args);
extern PyObject *tmpyl_tanh(PyObject *self, PyObject *args);
extern PyObject *tmpyl_trunc(PyObject *self, PyObject *args);
extern PyObject *tmpyl_unit_clamp(PyObject *self, PyObject *args);

#endif
/*  End of include guard.                                                     */