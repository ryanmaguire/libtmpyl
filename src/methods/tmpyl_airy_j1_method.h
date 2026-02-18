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
#ifndef TMPYL_AIRY_J1_METHOD_H
#define TMPYL_AIRY_J1_METHOD_H
#define TMPYL_AIRY_J1_METHOD                                                   \
{                                                                              \
    "airy_j1",                                                                 \
    tmpyl_airy_j1,                                                             \
    METH_VARARGS,                                                              \
    "\rFunction:\n"                                                            \
    "\r    tmpyl.airy_j1\n"                                                    \
    "\rPurpose:\n"                                                             \
    "\r    Computes the first Airy diffraction function, 2 J1(x) / x.\n"       \
    "\rArguments\n"                                                            \
    "\r    x:\n"                                                               \
    "\r        The independent variable (int, float,\n"                        \
    "\r        list, or numpy array).\n"                                       \
    "\rOutputs:\n"                                                             \
    "\r    aij1_x:\n"                                                          \
    "\r        The Airy J1 function of x.\n"                                   \
    "\rExample:\n"                                                             \
    "\r    >>> import numpy\n"                                                 \
    "\r    >>> import tmpyl\n"                                                 \
    "\r    >>> x = numpy.arange(-1, 1, 1.0E-3)\n"                              \
    "\r    >>> y = tmpyl.airy_j1(x)"                                           \
}
#endif
