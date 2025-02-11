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
#ifndef TMPYL_BESSEL_J1_METHOD_H
#define TMPYL_BESSEL_J1_METHOD_H
#define TMPYL_BESSEL_J1_METHOD                                                 \
{                                                                              \
    "bessel_j1",                                                               \
    tmpyl_bessel_j1,                                                           \
    METH_VARARGS,                                                              \
    "\r"                                                                       \
    "Function:"                                                                \
    "\n\r    "                                                                 \
    "tmpyl.bessel_j1"                                                          \
    "\n\r"                                                                     \
    "Purpose:"                                                                 \
    "\n\r    "                                                                 \
    "Computes the first Bessel function of the first kind (J1)."               \
    "\n\r"                                                                     \
    "Arguments"                                                                \
    "\n\r    "                                                                 \
    "x:"                                                                       \
    "\n\r        "                                                             \
    "The independent variable (int, float, complex, list, or numpy array)."    \
    "\n\r"                                                                     \
    "Outputs:"                                                                 \
    "\n\r    "                                                                 \
    "J0_x:"                                                                    \
    "\n\r        "                                                             \
    "The zeroth Bessel function of the first kind evaluated at x."             \
    "\n\r"                                                                     \
    "Example:"                                                                 \
    "\n\r    "                                                                 \
    ">>> import numpy"                                                         \
    "\n\r    "                                                                 \
    ">>> import tmpyl"                                                         \
    "\n\r    "                                                                 \
    ">>> x = numpy.arange(-1.0, 1.0, 0.01)"                                    \
    "\n\r    "                                                                 \
    ">>> y = tmpyl.bessel_j1(x)"                                               \
}
#endif
