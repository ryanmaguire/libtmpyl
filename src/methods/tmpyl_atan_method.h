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
#ifndef TMPYL_ATAN_METHOD_H
#define TMPYL_ATAN_METHOD_H
#define TMPYL_ATAN_METHOD                                                      \
{                                                                              \
    "atan",                                                                    \
    tmpyl_atan,                                                                \
    METH_VARARGS,                                                              \
    "\rFunction:\n"                                                            \
    "\r    tmpyl.atan\n"                                                       \
    "\rPurpose:\n"                                                             \
    "\r    Computes the inverse tangent of the input.\n"                       \
    "\rArguments\n"                                                            \
    "\r    x:\n"                                                               \
    "\r        The independent variable (int, float,\n"                        \
    "\r        list, or numpy array).\n"                                       \
    "\rOutputs:\n"                                                             \
    "\r    atan_x:\n"                                                          \
    "\r        The inverse tangent of x.\n"                                    \
    "\rExample:\n"                                                             \
    "\r    >>> import numpy\n"                                                 \
    "\r    >>> import tmpyl\n"                                                 \
    "\r    >>> x = numpy.arange(-100, 100, 1.0E-1)\n"                          \
    "\r    >>> y = tmpyl.atan(x)"                                              \
}
#endif
