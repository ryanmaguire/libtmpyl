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
#ifndef TMPYL_CBRT_METHOD_H
#define TMPYL_CBRT_METHOD_H
#define TMPYL_CBRT_METHOD                                                      \
{                                                                              \
    "cbrt",                                                                    \
    tmpyl_cbrt,                                                                \
    METH_VARARGS,                                                              \
    "\r"                                                                       \
    "Function:"                                                                \
    "\n\r    "                                                                 \
    "tmpyl.cbrt"                                                               \
    "\n\r"                                                                     \
    "Purpose:"                                                                 \
    "\n\r    "                                                                 \
    "Computes the cube root of the input."                                     \
    "\n\r"                                                                     \
    "Arguments"                                                                \
    "\n\r    "                                                                 \
    "x:"                                                                       \
    "\n\r        "                                                             \
    "The independent variable (int, float, complex, list, or numpy array)."    \
    "\n\r"                                                                     \
    "Outputs:"                                                                 \
    "\n\r    "                                                                 \
    "cbrt_x:"                                                                  \
    "\n\r        "                                                             \
    "The cube root of x."                                                      \
    "\n\r"                                                                     \
    "Notes:"                                                                   \
    "\n\r    "                                                                 \
    "For complex arguments the branch cut occurs along the negative"           \
    "\n\r    "                                                                 \
    "real axis."                                                               \
    "\n\r"                                                                     \
    "Example:"                                                                 \
    "\n\r    "                                                                 \
    ">>> import numpy"                                                         \
    "\n\r    "                                                                 \
    ">>> import tmpyl"                                                         \
    "\n\r    "                                                                 \
    ">>> x = numpy.arange(-1.0, 1.0, 0.01)"                                    \
    "\n\r    "                                                                 \
    ">>> y = tmpyl.cbrt(x)"                                                    \
}
#endif
