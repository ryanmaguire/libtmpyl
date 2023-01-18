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
#include "tmpyl_atan_method.h"
#include "tmpyl_atan_pade_method.h"
#include "tmpyl_atan_maclaurin_method.h"
#include "tmpyl_besselI0_method.h"
#include "tmpyl_besselJ0_method.h"
#include "tmpyl_cbrt_method.h"
#include "tmpyl_cos_method.h"
#include "tmpyl_cosd_method.h"
#include "tmpyl_fresnel_cos_method.h"
#include "tmpyl_fresnel_sin_method.h"
#include "tmpyl_lambertw_method.h"
#include "tmpyl_log_method.h"
#include "tmpyl_mod_2_method.h"
#include "tmpyl_mod_360_method.h"
#include "tmpyl_sinc_method.h"
#include "tmpyl_sind_method.h"

/*  All of the methods of the tmpyl module are defined in this array.         */
static PyMethodDef tmpyl_methods[] =
{
    TMPYL_ABS_METHOD,
    TMPYL_ACOS_METHOD,
    TMPYL_ATAN_METHOD,
    TMPYL_ATAN_PADE_METHOD,
    TMPYL_ATAN_MACLAURIN_METHOD,
    TMPYL_BESSELI0_METHOD,
    TMPYL_BESSELJ0_METHOD,
    TMPYL_CBRT_METHOD,
    TMPYL_COS_METHOD,
    TMPYL_COSD_METHOD,
    TMPYL_FRESNEL_COS_METHOD,
    TMPYL_FRESNEL_SIN_METHOD,
    TMPYL_LAMBERTW_METHOD,
    TMPYL_LOG_METHOD,
    TMPYL_MOD_2_METHOD,
    TMPYL_MOD_360_METHOD,
    TMPYL_SINC_METHOD,
    TMPYL_SIND_METHOD,
    {NULL, NULL, 0, NULL}
};

/*  The following code uses the Python 3 API. Check the version first.        */
#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "tmpyl",
    NULL,
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
