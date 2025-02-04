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
tmpyl_Get_Py_Out_From_Numpy_Array(PyObject * const x,
                                  const tmpyl_GenericFunctionObj * const c_func)
{
    /*  Signed and unsigned variables for the dimensions of the numpy array.  */
    size_t dim;
    npy_intp np_dim;

    /*  The data in a numpy array is returned as a void pointer.              */
    const void *data;
    void *out;

    /*  typenum for the data type the void pointer represents.                */
    int typenum;

    /*  And pointers for handling the data.                                   */
    PyArrayObject *x_as_arr;
    PyObject *capsule, *output;

    /*  If the input is a NULL pointer, abort.                                */
    if (x == NULL)
        goto FAILURE;

    /*  Similarly if the function pointer is NULL.                            */
    else if (c_func == NULL)
        goto FAILURE;

    /*  Otherwise, check if this variable is NULL. If it is, we MUST call the *
     *  numpy function import_array. Failure to do so will result in a        *
     *  segmentation fault, crashing the program.                             */
    else if (PyArray_API == NULL)
        import_array();

    /*  We need to treat the pointer to the Python object as a pointer to a   *
     *  numpy array. The numpy documentation states it is safe to perform     *
     *  such a cast.                                                          */
    x_as_arr = (PyArrayObject *)x;

    /*  Check the input to make sure it is valid. tmpyl only accepts          *
     *  1 dimensional numpy arrays.                                           */
    if (PyArray_NDIM(x_as_arr) != 1)
    {
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n"
                         "\n\rInput is not 1-dimensional.\n");
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\n\rInput is not 1-dimensional.\n",
                         c_func->func_name);
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
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                        "\n\rError Encountered: tmpyl\n"
                        "\r\tFunction Name: Unknown\n"
                        "\n\n\rInput numpy array is empty.\n");
        else
            PyErr_Format(PyExc_RuntimeError,
                        "\n\rError Encountered: tmpyl\n"
                        "\r\tFunction Name: %s\n\n"
                        "\n\n\rInput numpy array is empty.\n",
                        c_func->func_name);
        return NULL;
    }

    /*  Perform the computation based on the type of data we have.            */
    switch (typenum)
    {
        /*  float in C.                                                       */
        case NPY_FLOAT:

            /*  This function is real in, real out.                           */
            if (c_func->f2f != NULL)
            {
                /*  Allocate memory for the output.                           */
                out = malloc(sizeof(float) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_F2F(data, out, dim, c_func->f2f);
            }

            /*  This function is real in, complex out.                        */
            else if (c_func->f2cf != NULL)
            {
                /*  The output is a complex float, so change typenum to this. */
                typenum = NPY_CFLOAT;

                /*  Allocate memory for the output.                           */
                out = malloc(sizeof(tmpl_ComplexFloat) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_F2CF(data, out, dim, c_func->f2cf);
            }

            /*  If neither exists, the function does not support float.       */
            else
                goto FAILURE;

            break;

        /*  double in C.                                                      */
        case NPY_DOUBLE:

            /*  This function is real in, real out.                           */
            if (c_func->d2d != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_D2D(data, out, dim, c_func->d2d);
            }

            /*  Otherwise, check for real in, complex out.                    */
            else if (c_func->d2cd != NULL)
            {
                /*  The output is a complex double, so change typenum to this.*/
                typenum = NPY_CDOUBLE;

                /*  Allocate memory for the output.                           */
                out = malloc(sizeof(tmpl_ComplexDouble) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_D2CD(data, out, dim, c_func->d2cd);
            }

            /*  If neither exists, the function does not support double.      */
            else
                goto FAILURE;

            break;

        case NPY_LONGDOUBLE:

            /*  This function is real in, real out.                           */
            if (c_func->ld2ld != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(long double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_LD2LD(data, out, dim, c_func->ld2ld);
            }

            /*  Otherwise, check for real in, complex out.                    */
            else if (c_func->ld2cld != NULL)
            {
                /*  The output is a complex long double, so change typenum.   */
                typenum = NPY_CLONGDOUBLE;

                /*  Allocate memory for the output.                           */
                out = malloc(sizeof(tmpl_ComplexLongDouble) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_LD2CLD(data, out, dim, c_func->ld2cld);
            }

            /*  If neither exists, the function does not support long double. */
            else
                goto FAILURE;

            break;

        case NPY_CFLOAT:

            /*  This function is complex in, complex out.                     */
            if (c_func->cf2cf != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(tmpl_ComplexFloat) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CF2CF(data, out, dim, c_func->cf2cf);
            }

            /*  This function is complex in, real out.                        */
            else if (c_func->cf2f != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(float) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  The output is a float, so change typenum.                 */
                typenum = NPY_FLOAT;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CF2F(data, out, dim, c_func->cf2f);
            }

            /*  If neither exists, the function does not support complex.     */
            else
                goto FAILURE;

            break;

        case NPY_CDOUBLE:

            /*  This function is complex in, complex out.                     */
            if (c_func->cd2cd != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(tmpl_ComplexDouble) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CD2CD(data, out, dim, c_func->cd2cd);
            }

            /*  This function is complex in, real out.                        */
            else if (c_func->cd2d != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  The output is a double, so change typenum.                */
                typenum = NPY_DOUBLE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CD2D(data, out, dim, c_func->cd2d);
            }

            /*  If neither exists, the function does not support complex.     */
            else
                goto FAILURE;

            break;

        case NPY_CLONGDOUBLE:

            /*  This function is complex in, complex out.                     */
            if (c_func->cld2cld != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(tmpl_ComplexLongDouble) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CLD2CLD(data, out, dim, c_func->cld2cld);
            }

            /*  This function is complex in, real out.                        */
            else if (c_func->cld2ld != NULL)
            {
                /*  Allocate memory for the output data.                      */
                out = malloc(sizeof(long double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  The output is a long double, so change typenum.           */
                typenum = NPY_LONGDOUBLE;

                /*  Otherwise, pass the data and the function pointer to      *
                 *  libtmpl for computation.                                  */
                tmpl_Void_Array_CLD2LD(data, out, dim, c_func->cld2ld);
            }

            /*  If neither exists, the function does not support complex.     */
            else
                goto FAILURE;

            break;

        /*  Integer inputs.                                                   */
        case NPY_LONG:
            if (c_func->l2l != NULL)
            {
                /*  Allocate memory for the output.                           */
                out = malloc(sizeof(long) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  If not, perform the computation.                          */
                tmpl_Void_Array_L2L(data, out, dim, c_func->l2l);
            }

            /*  If no integer value function exists, try converting to real.  */
            else if (c_func->d2d != NULL)
            {
                /*  Try to convert the data to double.                        */
                out = malloc(sizeof(double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  The output is double, so change typenum.                  */
                typenum = NPY_DOUBLE;

                /*  Perform the computation in libtmpl.                       */
                tmpl_Void_Array_L2D(data, out, dim, c_func->d2d);
            }

            else if (c_func->d2cd != NULL)
            {
                /*  Try to convert the data to double.                        */
                out = malloc(sizeof(double) * dim);

                /*  Check if malloc failed.                                   */
                if (out == NULL)
                    goto MALLOC_FAILURE;

                /*  The output is complex double, so change typenum.          */
                typenum = NPY_CDOUBLE;

                /*  Perform the computation in libtmpl.                       */
                tmpl_Void_Array_L2CD(data, out, dim, c_func->d2cd);
            }

            /*  If none of these exist, the function does not support long.   */
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
    if (c_func->func_name == NULL)
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: Unknown\n\n"
                     "\rCould not parse inputs.\n");
    else
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: %s\n\n"
                     "\rCould not parse inputs.\n",
                     c_func->func_name);
    return NULL;

MALLOC_FAILURE:
    if (c_func->func_name == NULL)
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: Unknown\n\n"
                     "\rmalloc failed to allocate memory. Aborting.\n");
    else
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: %s\n\n"
                     "\rmalloc failed to allocate memory. Aborting.\n",
                     c_func->func_name);
    return NULL;
}

#endif
/*  End of #if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1.              */

/*  This function passes integer objects to C for computation.                */
static PyObject *
tmpyl_Get_Py_Out_From_Long(PyObject * const x,
                           const tmpyl_GenericFunctionObj * const c_func)
{
    /*  If the the tmpyl_GenericFunctionObj pointer contains an integer       *
     *  function (integer in, integer out), use this.                         */
    if (c_func->l2l != NULL)
    {
        /*  Extract the data from Python as a long int.                       */
        long int x_int = PyLong_AsLong(x);

        /*  Pass the input to the C function.                                 */
        long int y_int = c_func->l2l(x_int);

        /*  Convert the integer into a PyObject pointer with PyLong_FromLong. */
        return PyLong_FromLong(y_int);
    }

    /*  If there's no integer-to-integer function, try a double-to-double     *
     *  function. The resulting PyObject will be a float object.              */
    else if (c_func->d2d != NULL)
    {
        /*  Convert the integer object into a double.                         */
        double x_val = PyLong_AsDouble(x);

        /*  Pass the data to the C function for computation.                  */
        double y_val = c_func->d2d(x_val);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  Lastly, check if there is a function that takes in a real value and   *
     *  returns a complex value. If there is, the output will be a complex    *
     *  Python object (i.e. complex number in Python).                        */
    else if (c_func->d2cd != NULL)
    {
        /*  Extract the data from the PyObject and convert it to a double.    */
        double x_in = PyLong_AsDouble(x);

        /*  Run the computation, creating a tmpl_ComplexDouble in the process.*/
        tmpl_ComplexDouble z_out = c_func->d2cd(x_in);

        /*  Python will not accept a tmpl_ComplexDouble struct as a valid     *
         *  complex number. We can create a complex object from two doubles,  *
         *  however. Extract the real and imaginary parts from z.             */
        double real = tmpl_CDouble_Real_Part(z_out);
        double imag = tmpl_CDouble_Imag_Part(z_out);

        /*  Create the complex object from two doubles and return.            */
        return PyComplex_FromDoubles(real, imag);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
/*  End of tmpl_Get_Py_Out_From_Long.                                         */

/*  Python 2 had the int data type. Python 3 combined int and long into 1     *
 *  data type. If PY_VERSION_HEX indicates Python 2, create an int function.  */
#if PY_VERSION_HEX < 0x03000000

/*  This function passes integer objects to C for computation.                */
static PyObject *
tmpyl_Get_Py_Out_From_Int(PyObject * const x,
                         const tmpyl_GenericFunctionObj * const c_func)
{
    /*  If the the tmpyl_GenericFunctionObj pointer contains an integer       *
     *  function (integer in, integer out), use this.                         */
    if (c_func->l2l != NULL)
    {
        /*  Extract the data from Python as a long int.                       */
        long int x_int = PyInt_AsLong(x);

        /*  Pass the input to the C function.                                 */
        long int y_int = c_func->l2l(x_int);

        /*  Convert the integer into a PyObject pointer with PyInt_FromLong.  */
        return PyInt_FromLong(y_int);
    }

    /*  If there's no integer-to-integer function, try a double-to-double     *
     *  function. The resulting PyObject will be a float object.              */
    else if (c_func->d2d != NULL)
    {
        /*  Convert the integer object into a double.                         */
        long int x_int = PyInt_AsLong(x);
        double x_val = (double)x_int;

        /*  Pass the data to the C function for computation.                  */
        double y_val = c_func->d2d(x_val);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  Lastly, check if there is a function that takes in a real value and   *
     *  returns a complex value. If there is, the output will be a complex    *
     *  Python object (i.e. complex number in Python).                        */
    else if (c_func->d2cd != NULL)
    {
        /*  Extract the data from the PyObject and convert it to a double.    */
        long int x_int = PyInt_AsLong(x);
        double x_in = (double)x_int;

        /*  Run the computation, creating a tmpl_ComplexDouble in the process.*/
        tmpl_ComplexDouble z_out = c_func->d2cd(x_in);

        /*  Python will not accept a tmpl_ComplexDouble struct as a valid     *
         *  complex number. We can create a complex object from two doubles,  *
         *  however. Extract the real and imaginary parts from z.             */
        double real = tmpl_CDouble_Real_Part(z_out);
        double imag = tmpl_CDouble_Imag_Part(z_out);

        /*  Create the complex object from two doubles and return.            */
        return PyComplex_FromDoubles(real, imag);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rInteger input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
/*  End of tmpl_Get_Py_Out_From_Int.                                          */

#endif
/*  End of #if PY_VERSION_HEX < 0x03000000.                                   */

/*  Function for passing a float object to C for computation.                 */
static PyObject *
tmpyl_Get_Py_Out_From_Float(PyObject * const x,
                            const tmpyl_GenericFunctionObj * const c_func)
{
    /*  Check if there's a double-to-double function. The resulting PyObject  *
     *  will by a float object.                                               */
    if (c_func->d2d != NULL)
    {
        /*  Convert the float object into a double.                           */
        double x_val = PyFloat_AsDouble(x);

        /*  Pass the data to the C function for computation.                  */
        double y_val = c_func->d2d(x_val);

        /*  Convert the double to a PyObject pointer for a float and return.  */
        return PyFloat_FromDouble(y_val);
    }

    /*  Lastly, check if there is a function that takes in a real value and   *
     *  returns a complex value. If there is, the output will be a complex    *
     *  Python object (i.e. complex number in Python).                        */
    else if (c_func->d2cd != NULL)
    {
        /*  Extract the data from the PyObject and convert it to a double.    */
        double x_in = PyFloat_AsDouble(x);

        /*  Run the computation, creating a tmpl_ComplexDouble in the process.*/
        tmpl_ComplexDouble z_out = c_func->d2cd(x_in);

        /*  Python will not accept a tmpl_ComplexDouble struct as a valid     *
         *  complex number. We can create a complex object from two doubles,  *
         *  however. Extract the real and imaginary parts from z.             */
        double real = tmpl_CDouble_Real_Part(z_out);
        double imag = tmpl_CDouble_Imag_Part(z_out);

        /*  Create the complex object from two doubles and return.            */
        return PyComplex_FromDoubles(real, imag);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rFloat input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.");

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rFloat input provided but this function does not\n"
                         "\rexcept real valued (float or int) arguments.",
                         c_func->func_name);

        return NULL;
    }
}
/*  tmpl_Get_Py_Out_From_Float.                                               */

/*  Function for passing complex Python objects to C for computation.         */
static PyObject *
tmpyl_Get_Py_Out_From_Complex(PyObject * const x,
                              const tmpyl_GenericFunctionObj * const c_func)
{
    /*  Check if there is a function that takes a complex number in and       *
     *  returns a complex number.                                             */
    if (c_func->cd2cd)
    {
        /*  Extract the real and imaginary parts from the complex number.     */
        double real_in = PyComplex_RealAsDouble(x);
        double imag_in = PyComplex_ImagAsDouble(x);

        /*  Convert this data into a tmpl_ComplexDouble struct.               */
        tmpl_ComplexDouble z_in = tmpl_CDouble_Rect(real_in, imag_in);

        /*  Pass the data to the function.                                    */
        tmpl_ComplexDouble z_out = c_func->cd2cd(z_in);

        /*  Extract the real and imaginary parts from the output.             */
        double real_out = tmpl_CDouble_Real_Part(z_out);
        double imag_out = tmpl_CDouble_Imag_Part(z_out);

        /*  Convert this to a Python complex object and return.               */
        return PyComplex_FromDoubles(real_out, imag_out);
    }

    /*  Check if there's a complex-to-real function, like complex modulus.    */
    else if (c_func->cd2d)
    {
        /*  Extract the real and imaginary parts from the complex number.     */
        double real_in = PyComplex_RealAsDouble(x);
        double imag_in = PyComplex_ImagAsDouble(x);

        /*  Convert this data into a tmpl_ComplexDouble struct.               */
        tmpl_ComplexDouble z_in = tmpl_CDouble_Rect(real_in, imag_in);

        /*  Pass the data to the function.                                    */
        double out = c_func->cd2d(z_in);

        /*  Convert to a float Python object and return.                      */
        return PyFloat_FromDouble(out);
    }

    /*  If there is no function that can handle the input, return with error. */
    else
    {
        /*  If the function name pointer is NULL, print the following error.  */
        if (c_func->func_name)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: %s\n\n"
                         "\rComplex input provided but this function does not\n"
                         "\rexcept complex arguments.", c_func->func_name);

        /*  Otherwise, print the error with the function name included.       */
        else
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rComplex input provided but this function does not\n"
                         "\rexcept complex arguments.");

        return NULL;
    }
}
/*  End of tmpyl_Get_Py_Out_From_Complex.                                     */

static PyObject *
tmpyl_Get_Py_Out_From_List(PyObject * const x,
                           const tmpyl_GenericFunctionObj * const c_func)
{
    PyObject *nth_item;
    PyObject *current_item;
    Py_ssize_t dim = PyList_Size(x);
    PyObject *output = PyList_New(dim);
    Py_ssize_t n;

    for (n = 0; n < dim; ++n)
    {
        nth_item = PyList_GetItem(x, n);

        if (PyLong_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Long(nth_item, c_func);

/*  Python 2 had the int data type. Python 3 combined int and long into 1     *
 *  data type. If PY_VERSION_HEX indicates Python 2, check for int.           */
#if PY_VERSION_HEX < 0x03000000
        else if (PyInt_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Int(nth_item, c_func);
#endif
/*  End of #if PY_VERSION_HEX >= 0x03000000                                   */

        else if (PyFloat_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Float(nth_item, c_func);

        else if (PyComplex_Check(nth_item))
            current_item = tmpyl_Get_Py_Out_From_Complex(nth_item, c_func);

        else
        {
            if (c_func->func_name == NULL)
            PyErr_Format(PyExc_RuntimeError,
                         "\n\rError Encountered: tmpyl\n"
                         "\r\tFunction Name: Unknown\n\n"
                         "\rInput list must contain real or\n"
                         "\rcomplex numbers only.\n");
            else
                PyErr_Format(PyExc_RuntimeError,
                             "\n\rError Encountered: tmpyl\n"
                             "\r\tFunction Name: %s\n\n"
                             "\rInput list must contain real or\n"
                             "\rcomplex numbers only.\n",
                             c_func->func_name);
            return NULL;
        }

        PyList_SET_ITEM(output, n, current_item);
    }

    return output;
}

PyObject *
tmpl_Get_Py_Func_From_C(PyObject *self, PyObject *args,
                        const tmpyl_GenericFunctionObj * const c_func)
{
    /*  Declare necessary variables.                                          */
    PyObject *x;

    if ((args == NULL) || (c_func == NULL))
        goto FAILURE;

#if defined(TMPYL_HAS_NUMPY) && TMPYL_HAS_NUMPY == 1
    if (PyArray_API == NULL)
            import_array();
#endif

    /*  Parse the data from Python and try to convert it to a usable format.  */
    if (!PyArg_ParseTuple(args, "O", &x))
        goto FAILURE;

    if (PyLong_Check(x))
        return tmpyl_Get_Py_Out_From_Long(x, c_func);

/*  Python 2 had the int data type. Python 3 combined int and long into 1     *
 *  data type. If PY_VERSION_HEX indicates Python 2, check for int.           */
#if PY_VERSION_HEX < 0x03000000
    else if (PyInt_Check(x))
        return tmpyl_Get_Py_Out_From_Int(x, c_func);
#endif
/*  End of #if PY_VERSION_HEX >= 0x03000000                                   */

    else if (PyFloat_Check(x))
        return tmpyl_Get_Py_Out_From_Float(x, c_func);
    else if (PyComplex_Check(x))
        return tmpyl_Get_Py_Out_From_Complex(x, c_func);
    else if (PyList_Check(x))
        return tmpyl_Get_Py_Out_From_List(x, c_func);

#if TMPYL_HAS_NUMPY == 1
    else if (PyArray_Check(x))
        return tmpyl_Get_Py_Out_From_Numpy_Array(x, c_func);
#endif
    goto FAILURE;

FAILURE:
    if (c_func->func_name == NULL)
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: Unknown\n\n"
                     "\rCould not parse inputs.\n");
    else
        PyErr_Format(PyExc_RuntimeError,
                     "\n\rError Encountered: tmpyl\n"
                     "\r\tFunction Name: %s\n\n"
                     "\rCould not parse inputs.\n",
                     c_func->func_name);
    return NULL;
}
