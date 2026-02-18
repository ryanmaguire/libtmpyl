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
 *                               tmpyl_methods                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the "methods" for the libtmpl functions, which allow them to *
 *      be called from Python.                                                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the Python-C API.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPYL_METHODS_H
#define TMPYL_METHODS_H

/*  The Python-C API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*  Methods for all of the libtmpl functions.                                 */
#include "methods/tmpyl_abs_method.h"
#include "methods/tmpyl_acos_method.h"
#include "methods/tmpyl_airy_j1_method.h"
#include "methods/tmpyl_asin_method.h"
#include "methods/tmpyl_atan_method.h"
#include "methods/tmpyl_bessel_i0_method.h"
#include "methods/tmpyl_bessel_j0_method.h"
#include "methods/tmpyl_bessel_j1_method.h"
#include "methods/tmpyl_cbrt_method.h"
#include "methods/tmpyl_ceil_method.h"
#include "methods/tmpyl_cos_method.h"
#include "methods/tmpyl_cosd_method.h"
#include "methods/tmpyl_cosh_method.h"
#include "methods/tmpyl_cospi_method.h"
#include "methods/tmpyl_erf_method.h"
#include "methods/tmpyl_exp_method.h"
#include "methods/tmpyl_floor_method.h"
#include "methods/tmpyl_fractional_part_method.h"
#include "methods/tmpyl_fresnel_cos_method.h"
#include "methods/tmpyl_fresnel_sin_method.h"
#include "methods/tmpyl_lambertw_method.h"
#include "methods/tmpyl_log_method.h"
#include "methods/tmpyl_mod_2_method.h"
#include "methods/tmpyl_mod_360_method.h"
#include "methods/tmpyl_normalized_fresnel_cos_method.h"
#include "methods/tmpyl_normalized_fresnel_sin_method.h"
#include "methods/tmpyl_sin_method.h"
#include "methods/tmpyl_sinc_method.h"
#include "methods/tmpyl_sincpi_method.h"
#include "methods/tmpyl_sind_method.h"
#include "methods/tmpyl_sinh_method.h"
#include "methods/tmpyl_sinpi_method.h"
#include "methods/tmpyl_sqrt_method.h"
#include "methods/tmpyl_tan_method.h"
#include "methods/tmpyl_tanh_method.h"
#include "methods/tmpyl_trunc_method.h"
#include "methods/tmpyl_unit_clamp_method.h"

#endif
/*  End of include guard.                                                     */