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
#ifndef TMPYL_BESSEL_I0_METHOD_H
#define TMPYL_BESSEL_I0_METHOD_H
#define TMPYL_BESSEL_I0_METHOD                                                 \
{                                                                              \
    "bessel_i0",                                                               \
    tmpyl_bessel_i0,                                                           \
    METH_VARARGS,                                                              \
    "\rFunction:\n"                                                            \
    "\r    tmpyl.bessel_i0\n"                                                  \
    "\rPurpose:\n"                                                             \
    "\r    Computes the zeroth modified Bessel function\n"                     \
    "\r    of the first kind (I0).\n"                                          \
    "\rArguments\n"                                                            \
    "\r    x:\n"                                                               \
    "\r        The independent variable (int, float, complex,\n"               \
    "\r        list, or numpy array).\n"                                       \
    "\rOutputs:\n"                                                             \
    "\r    i0_x:\n"                                                            \
    "\r        The zeroth modified Bessel function of\n"                       \
    "\r        the first kind evaluated at x.\n"                               \
    "\rExample:\n"                                                             \
    "\r    >>> import numpy\n"                                                 \
    "\r    >>> import tmpyl\n"                                                 \
    "\r    >>> x = numpy.arange(-1.0, 1.0, 0.01)\n"                            \
    "\r    >>> y = tmpyl.bessel_i0(x)\n"                                       \
}
#endif
