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
#ifndef TMPYL_KBMD20_METHOD_H
#define TMPYL_KBMD20_METHOD_H
#define TMPYL_KBMD20_METHOD                                                    \
{                                                                              \
    "kbmd20",                                                                  \
    tmpyl_kbmd20,                                                              \
    METH_VARARGS,                                                              \
    "\rFunction:\n"                                                            \
    "\r    tmpyl.kbmd20\n"                                                     \
    "\rPurpose:\n"                                                             \
    "\r    Computes the modified Kaiser-Bessel window (alpha = 2.0).\n"        \
    "\rArguments\n"                                                            \
    "\r    x:\n"                                                               \
    "\r        The independent variable (int, float,\n"                        \
    "\r        list, or numpy array).\n"                                       \
    "\r    w:\n"                                                               \
    "\r        The window width (float).\n"                                    \
    "\rOutputs:\n"                                                             \
    "\r    kbmd20_x:\n"                                                        \
    "\r        The inverse cosine of x.\n"                                     \
    "\rExample:\n"                                                             \
    "\r    >>> import numpy\n"                                                 \
    "\r    >>> import tmpyl\n"                                                 \
    "\r    >>> x = numpy.arange(-1, 1, 0.01)\n"                                \
    "\r    >>> w = 0.5\n"                                                      \
    "\r    >>> y = tmpyl.kbmd20(x, w)"                                         \
}
#endif
