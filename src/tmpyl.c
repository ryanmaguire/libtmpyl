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
 ******************************************************************************
 *                                   tmpyl                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file defines all of the function in the Python module tmpyl at   *
 *      the C level. There is no actual Python code, but rather the Python-C  *
 *      API is used to write python wrappers for libtmpl functions.           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) libtmpl:                                                              *
 *          libtmpl (the C library) must be built prior to building tmpyl.    *
 *          The setup.py script attempts to link libtmpl.so to this.          *
 *  2.) CPython:                                                              *
 *          The file Python.h is required, which comes part of the CPython    *
 *          implementation of the Python programming language.                *
 *  3.) numpy:                                                                *
 *          OPTIONAL. Macros are used to handle the case where numpy is not   *
 *          available. The Numpy C API is used so that numpy arrays can be    *
 *          used with the functions from libtmpl. If you do not have numpy,   *
 *          you can still use libtmpl with lists, floats, and ints in Python. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 31, 2021                                               *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/08/31: Ryan Maguire                                                  *
 *      Added license and doc string.                                         *
 ******************************************************************************/

/*  To avoid compiler warnings about deprecated numpy stuff. This line is     *
 *  recommended in the numpy documentation. If TMPYL_HAS_NUMPY is 0, numpy is *
 *  not available so we don't need this macro.                                */
#if TMPYL_HAS_NUMPY == 1
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

/*  The Python-C API is given here. The Python documentation recommends       *
 *  including Python.h before anything (even standard library headers).       */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*  If numpy is available, we'll need to include the numpy header files.      */
#if TMPYL_HAS_NUMPY == 1
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>
#endif

/*  All of the needed Python-to-C tools are defined here.                     */
#include "tmpyl_common.h"

/*  The PyMethodDef structs for the functions are in their own header files.  */
#include "tmpyl_abs_method.h"
#include "tmpyl_acos_method.h"
#include "tmpyl_asin_method.h"
#include "tmpyl_atan_method.h"
#include "tmpyl_airy_j1_method.h"
#include "tmpyl_bessel_i0_method.h"
#include "tmpyl_bessel_j0_method.h"
#include "tmpyl_bessel_j1_method.h"
#include "tmpyl_cbrt_method.h"
#include "tmpyl_ceil_method.h"
#include "tmpyl_cos_method.h"
#include "tmpyl_cosd_method.h"
#include "tmpyl_cosh_method.h"
#include "tmpyl_cospi_method.h"
#include "tmpyl_erf_method.h"
#include "tmpyl_exp_method.h"
#include "tmpyl_floor_method.h"
#include "tmpyl_fractional_part_method.h"
#include "tmpyl_fresnel_cos_method.h"
#include "tmpyl_fresnel_sin_method.h"
#include "tmpyl_lambertw_method.h"
#include "tmpyl_log_method.h"
#include "tmpyl_mod_2_method.h"
#include "tmpyl_mod_360_method.h"
#include "tmpyl_normalized_fresnel_cos_method.h"
#include "tmpyl_normalized_fresnel_sin_method.h"
#include "tmpyl_sin_method.h"
#include "tmpyl_sinc_method.h"
#include "tmpyl_sincpi_method.h"
#include "tmpyl_sind_method.h"
#include "tmpyl_sinh_method.h"
#include "tmpyl_sinpi_method.h"
#include "tmpyl_sqrt_method.h"
#include "tmpyl_tan_method.h"
#include "tmpyl_tanh_method.h"
#include "tmpyl_trunc_method.h"
#include "tmpyl_unit_clamp_method.h"

/*  All of the methods of the tmpyl module are defined in this array.         */
static PyMethodDef tmpyl_methods[] =
{
    TMPYL_ABS_METHOD,
    TMPYL_ACOS_METHOD,
    TMPYL_ASIN_METHOD,
    TMPYL_ATAN_METHOD,
    TMPYL_AIRY_J1_METHOD,
    TMPYL_BESSEL_I0_METHOD,
    TMPYL_BESSEL_J0_METHOD,
    TMPYL_BESSEL_J1_METHOD,
    TMPYL_CBRT_METHOD,
    TMPYL_CEIL_METHOD,
    TMPYL_COS_METHOD,
    TMPYL_COSD_METHOD,
    TMPYL_COSH_METHOD,
    TMPYL_COSPI_METHOD,
    TMPYL_ERF_METHOD,
    TMPYL_EXP_METHOD,
    TMPYL_FLOOR_METHOD,
    TMPYL_FRACTIONAL_PART_METHOD,
    TMPYL_FRESNEL_COS_METHOD,
    TMPYL_FRESNEL_SIN_METHOD,
    TMPYL_LAMBERTW_METHOD,
    TMPYL_LOG_METHOD,
    TMPYL_MOD_2_METHOD,
    TMPYL_MOD_360_METHOD,
    TMPYL_NORMALIZED_FRESNEL_COS_METHOD,
    TMPYL_NORMALIZED_FRESNEL_SIN_METHOD,
    TMPYL_SIN_METHOD,
    TMPYL_SINC_METHOD,
    TMPYL_SINCPI_METHOD,
    TMPYL_SIND_METHOD,
    TMPYL_SINH_METHOD,
    TMPYL_SINPI_METHOD,
    TMPYL_SQRT_METHOD,
    TMPYL_TAN_METHOD,
    TMPYL_TANH_METHOD,
    TMPYL_TRUNC_METHOD,
    TMPYL_UNIT_CLAMP_METHOD,
    {NULL, NULL, 0, NULL}
};

/*  The following code uses the Python 3 API. Check the version first.        */
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "tmpyl",
    "\rThe Mathematicians Programming Library.\n"
    "\rThis is a Python wrapper for the C library libtmpl.\n\n"
    "\rIt provides functions commonly used in mathematics and physics,\n"
    "\rincluding a full implementation of libm (the C mathematical library),\n"
    "\rcomplex numbers, quaternions, double-double arithmetic, 2D, 3D, 4D,\n"
    "\r6D and arbitrary dimensional real and complex vectors, integer\n"
    "\rroutines common in number theory, knot theory tools, matrices and\n"
    "\rlinear algebra, Fresnel diffraction, Fraunhaufor diffraction,\n"
    "\rgeometry tools, functions common in optics and astronomy,\n"
    "\rsorting routines, functions for generating rasterized PPM graphics\n"
    "\rand vectorized SVG figures. FFT routines and many special functions\n"
    "\rare also provided.\n\n"
    "\rPlease note that not all of libtmpl is currently available in tmpyl.\n"
    "\rBoth libtmpl and libtmpyl are actively worked on, and tmpyl is\n"
    "\rgradually catching up.\n\n"
#if TMPYL_HAS_NUMPY == 1
    "\rThe version of tmpyl you have installed was compiled with numpy\n"
    "\rsupport. You may use numpy arrays with real or complex arguments\n"
    "\rwith many of tmpyl's functions.\n",
#else
    "\rThe version of tmpyl you have installed was not compiled with numpy\n"
    "\rsupport. You may not use numpy arrays with tmpyl's functions.\n"
    "\rIf you would like numpy support, please make sure numpy is installed\n"
    "\rand then recompile tmpyl from its source:\n"
    "\r\thttps://github.com/ryanmaguire/libtmpyl\n",
#endif
    -1,
    tmpyl_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_tmpyl(void)
{
    PyObject *m = PyModule_Create(&moduledef);
    if (!m)
        return NULL;

    /*  This line is REQUIRED for numpy support. Without it, a segmentation   *
     *  fault will occur crashing tmpyl.                                      */
#if TMPYL_HAS_NUMPY == 1
    import_array();
#endif

    return m;
}

/*  Below works with Python 2.                                                */
#else
PyMODINIT_FUNC inittmpyl(void)
{
    PyObject *m;

    m = Py_InitModule("tmpyl", tmpyl_methods);
    if (m == NULL)
        return;

    /*  This line is REQUIRED for numpy support. Without it, a segmentation   *
     *  fault will occur crashing tmpyl.                                      */
#if TMPYL_HAS_NUMPY == 1
    import_array();
#endif

}
#endif
