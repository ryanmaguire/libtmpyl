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
#include "../tmpyl_methods.h"

PyMethodDef tmpyl_methods tmpyl_abs_method = {
    "abs",
    tmpyl_abs,
    METH_VARARGS,
    "\r"
    "Function:"
    "\n\r    "
    "tmpyl.abs"
    "\n\r"
    "Purpose:"
    "\n\r    "
    "Computes the absolute value of the input."
    "\n\r"
    "Arguments"
    "\n\r    "
    "x:"
    "\n\r        "
    "The independent variable (int, float, complex, list, or numpy array)."
    "\n\r"
    "Outputs:"
    "\n\r    "
    "abs_x:"
    "\n\r        "
    "The absolute value of x."
    "\n\r"
    "Example:"
    "\n\r    "
    ">>> import numpy"
    "\n\r    "
    ">>> import tmpyl"
    "\n\r    "
    ">>> x = numpy.arange(-100, 100, 0.01)"
    "\n\r    "
    ">>> y = tmpyl.abs(x)"
}
