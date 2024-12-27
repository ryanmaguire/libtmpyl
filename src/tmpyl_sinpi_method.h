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
#ifndef TMPYL_SINPI_METHOD_H
#define TMPYL_SINPI_METHOD_H
#define TMPYL_SINPI_METHOD                                                     \
{                                                                              \
    "sinpi",                                                                   \
    tmpyl_sinpi,                                                               \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.sinpi\n\r\t"                                                        \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the function sinpi(x) = sin(pi x)."                               \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for sinpi(x). Allowed inputs are int,\n\r\t\t\t"     \
    "float, complex, list (of ints, floats, and complex),\n\r\t\t\t"           \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "sinpi_x:\n\r\t\t\t"                                                       \
    "The sinc functions as a function of x. Same type as input.\n\r\t"         \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.sinpi(x)"                                                   \
}
#endif
