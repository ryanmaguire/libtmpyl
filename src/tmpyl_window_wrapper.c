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
 *                              tmpyl_common                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for wrapping C functions for use in the Python         *
 *      programming language. In particular, the CPython implementation.      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) Python.h:                                                             *
 *          Header file that is part of the CPython implementation of the     *
 *          python programming language. It enables use of the Python-C API.  *
 *  2.) stdlib.h:                                                             *
 *          Standard C header file that contains the free function.           *
 *  3.) tmpl.h:                                                               *
 *          Header file for libtmpl.                                          *
 *  4.) tmpyl_common.h:                                                       *
 *          Header file that defines the generic function object.             *
 *                                                                            *
 *  If you want numpy support, you must have numpy installed and have the     *
 *  these additional headers available:                                       *
 *                                                                            *
 *  5.) ndarraytypes.h                                                        *
 *  6.) ufuncobject.h                                                         *
 *          Header files for the C-Numpy API.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 31, 2021                                               *
 ******************************************************************************/

/*  To avoid compiler warnings about deprecated numpy stuff. This is only     *
 *  needed if numpy is available. setup.py provides the TMPYL_HAS_NUMPY macro *
 *  and sets it to 1 if numpy is available, and 0 otherwise. Check this.      */
#if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

/*  The python documentation recommends defining this BEFORE including the    *
 *  Python.h header file.                                                     */
#define PY_SSIZE_T_CLEAN

/*  Python-C API tools here. Python documentation recommends including this   *
 *  file before standard library files.                                       */
#include <Python.h>

/*  free is here. Python.h should include this file already, but I've         *
 *  included it just in case.                                                 */
#include <stdlib.h>

/*  All libtmpl header files are included in this one file.                   */
#include <libtmpl/include/tmpl.h>

/*  Definition of the generic function object is here.                        */
#include "tmpyl_common.h"

/*  If numpy is available, we'll need to include the numpy header files.      */
#if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1
#include <numpy/ndarraytypes.h>
#include <numpy/ufuncobject.h>

/*  This function frees the memory allocated to a pointer by malloc when the  *
 *  corresponding variable is destroyed at the Python level. It is only       *
 *  needed for numpy arrays. Python's reference counting handles the memory   *
 *  for other objects (ints, floats, lists, etc.).                            */
static void tmpyl_capsule_cleanup(PyObject *capsule)
{
    /*  PyCapsule_GetPointer returns a pointer to the actual data inside the  *
     *  capsule. This is the data that needs to be freed when something like  *
     *  'del' is called at the Python level.                                  */
    void *memory = PyCapsule_GetPointer(capsule, NULL);

    /*  Free the data.                                                        */
    free(memory);
}
/*  End of tmpyl_capsule_cleanup.                                             */

/*  This function handles numpy arrays.                                       */
static PyObject *
tmpyl_window_from_numpy_array(PyObject * const x,
                              const double width,
                              const tmpyl_WindowObj * const w_func)
{
    /*  Signed and unsigned variables for the dimensions of the numpy array.  */
    size_t n, dim;
    npy_intp np_dim;

    /*  The data in a numpy array is returned as a void pointer.              */
    const void *data;
    void *out;

    /*  typenum for the data type the void pointer represents.                */
    int typenum;

    /*  And pointers for handling the data.                                   */
    PyArrayObject *x_as_arr;
    PyObject *capsule, *output;

    /*  If the input or the window function is NULL, abort.                   */
    if (!x || !w_func)
        goto FAILURE;

    /*  Otherwise, check if this variable is NULL. If it is, we MUST call the *
     *  numpy function import_array. Failure to do so will result in a        *
     *  segmentation fault, crashing the program.                             */
    if (PyArray_API == NULL)
        import_array();

    /*  We need to treat the pointer to the Python object as a pointer to a   *
     *  numpy array. The numpy documentation states it is safe to perform     *
     *  such a cast.                                                          */
    x_as_arr = (PyArrayObject *)x;

    /*  Check the input to make sure it is valid. tmpyl only accepts          *
     *  1 dimensional numpy arrays.                                           */
    if (PyArray_NDIM(x_as_arr) != 1)
    {
        PyErr_Format(
            PyExc_RuntimeError,
            "\n\rError Encountered: tmpyl\n"
            "\r\tFunction Name: %s\n\n"
            "\n\rInput is not 1-dimensional.\n",
            w_func->func_name
        );

        return NULL;
    }

    /*  Extract useful data about the array.                                  */
    typenum = PyArray_TYPE(x_as_arr);
    np_dim = PyArray_DIM(x_as_arr, 0);
    data = PyArray_DATA(x_as_arr);

    if (np_dim < 0)
        goto FAILURE;

    dim = (size_t)np_dim;

    /*  Check that the array is not empty.                                    */
    if (dim == 0)
    {
        PyErr_Format(
            PyExc_RuntimeError,
            "\n\rError Encountered: tmpyl\n"
            "\r\tFunction Name: %s\n\n"
            "\n\n\rInput numpy array is empty.\n",
            w_func->func_name
        );

        return NULL;
    }

    /*  Perform the computation based on the type of data we have.            */
    switch (typenum)
    {
        /*  float in C.                                                       */
        case NPY_FLOAT:

            /*  This function is real in, real out.                           */
            if (w_func->fwindow)
            {
                const float fwidth = (float)width;
                const float * const in = data;
                float * const out_vals = malloc(sizeof(float) * dim);

                /*  Check if malloc failed.                                   */
                if (!out_vals)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                for (n = 0; n < dim; ++n)
                    out_vals[n] = w_func->fwindow(in[n], fwidth);

                out = out_vals;
            }

            /*  The function does not support float, abort.                   */
            else
                goto FAILURE;

            break;

        /*  double in C.                                                      */
        case NPY_DOUBLE:

            /*  This function is real in, real out.                           */
            if (w_func->dwindow)
            {
                const double * const in = data;
                double * const out_vals = malloc(sizeof(double) * dim);

                /*  Check if malloc failed.                                   */
                if (!out_vals)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                for (n = 0; n < dim; ++n)
                    out_vals[n] = w_func->dwindow(in[n], width);

                out = out_vals;
            }

            /*  The function does not support double, abort.                  */
            else
                goto FAILURE;

            break;

        case NPY_LONGDOUBLE:

            /*  This function is real in, real out.                           */
            if (w_func->ldwindow)
            {
                long double ldwidth = (long double)width;
                const long double * const in = data;
                long double *out_vals = malloc(sizeof(long double) * dim);

                /*  Check if malloc failed.                                   */
                if (!out_vals)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                for (n = 0; n < dim; ++n)
                    out_vals[n] = w_func->ldwindow(in[n], ldwidth);

                out = out_vals;
            }

            /*  The function does not support long double, abort.             */
            else
                goto FAILURE;

            break;

        /*  The function does not support the type of the input array. Abort. */
        default:
            goto FAILURE;
    }
    /*  End of switch (typenum).                                              */

    output = PyArray_SimpleNewFromData(1, &np_dim, typenum, out);
    capsule = PyCapsule_New(out, NULL, tmpyl_capsule_cleanup);

    /*  This frees the variable at the Python level once it's destroyed.  */
    PyArray_SetBaseObject((PyArrayObject *)output, capsule);

    /*  Return the results to Python.                                     */
    return Py_BuildValue("N", output);

FAILURE:

    PyErr_Format(
        PyExc_RuntimeError,
        "\n\rError Encountered: tmpyl\n"
        "\r\tFunction Name: %s\n\n"
        "\rCould not parse inputs.\n",
        w_func->func_name
    );

    return NULL;

MALLOC_FAILURE:

    PyErr_Format(
        PyExc_RuntimeError,
        "\n\rError Encountered: tmpyl\n"
        "\r\tFunction Name: %s\n\n"
        "\rmalloc failed to allocate memory. Aborting.\n",
        w_func->func_name
    );

    return NULL;
}

#endif
/*  End of #if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1.              */

/*  Function for passing a float object to C for computation.                 */
static PyObject *
tmpyl_window_from_float(PyObject * const x,
                        const double width,
                        const tmpyl_WindowObj * const w_func)
{
    /*  Check if there's a double-to-double function. The resulting PyObject  *
     *  will by a float object.                                               */
    if (w_func->dwindow)
    {
        /*  Convert the float object into a double.                           */
        double x_val = PyFloat_AsDouble(x);

        /*  Pass the data to the C function for computation.                  */
        double y_val = w_func->dwindow(x_val, width);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  If there is no function that can handle the input, return with error. */
    PyErr_Format(
        PyExc_RuntimeError,
        "\n\rError Encountered: tmpyl\n"
        "\r\tFunction Name: %s\n\n"
        "\rFloat input provided but this function does not\n"
        "\rexcept real valued (float or int) arguments.",
        w_func->func_name
    );

    return NULL;
}
/*  tmpyl_window_from_float.                                                  */

static PyObject *
tmpyl_window_from_list(PyObject * const x,
                       const double width,
                       const tmpyl_WindowObj * const w_func)
{
    const Py_ssize_t dim = PyList_Size(x);
    PyObject *output = PyList_New(dim);
    Py_ssize_t n;

    for (n = 0; n < dim; ++n)
    {
        PyObject *nth_item = PyList_GetItem(x, n);
        PyObject *value = tmpyl_window_from_float(nth_item, width, w_func);
        PyList_SET_ITEM(output, n, value);
    }

    return output;
}

PyObject *
tmpyl_window_wrapper(PyObject *self,
                     PyObject *args,
                     const tmpyl_WindowObj * const w_func)
{
    /*  Declare necessary variables.                                          */
    PyObject *x;
    double width;

    if (!args || ! w_func)
        goto FAILURE;

#if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1
    if (PyArray_API == NULL)
        import_array();
#endif

    /*  Parse the data from Python and try to convert it to a usable format.  */
    if (!PyArg_ParseTuple(args, "Od", &x, &width))
        goto FAILURE;

    if (PyFloat_Check(x) || PyLong_Check(x))
        return tmpyl_window_from_float(x, width, w_func);

    if (PyList_Check(x))
        return tmpyl_window_from_list(x, width, w_func);

#if TMPYL_HAS_NUMPY == 1
    if (PyArray_Check(x))
        return tmpyl_window_from_numpy_array(x, width, w_func);
#endif

FAILURE:

    PyErr_Format(
        PyExc_RuntimeError,
        "\n\rError Encountered: tmpyl\n"
        "\r\tFunction Name: %s\n\n"
        "\rCould not parse inputs.\n",
        w_func->func_name
    );

    return NULL;
}
