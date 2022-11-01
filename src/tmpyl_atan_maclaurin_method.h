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
#ifndef TMPYL_ATAN_MACLAURIN_METHOD_H
#define TMPYL_ATAN_MACLAURIN_METHOD_H
#define TMPYL_ATAN_MACLAURIN_METHOD                                            \
{                                                                              \
    "atan_maclaurin",                                                          \
    tmpyl_atan_maclaurin,                                                      \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.atan_maclaurin\n\r\t"                                               \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the first few terms of the Maclaurin series for arctangent."      \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for atan_maclaurin(x). Allowed inputs are int,\n\r\t"\
    "\t\tfloat, complex, list (of ints, floats, and complex),\n\r\t\t\t"       \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "atan_x:\n\r\t\t\t"                                                        \
    "The inverse tangent as a function of x. Same type as input.\n\r\t"        \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.atan_maclaurin(x)"                                          \
}
#endif
