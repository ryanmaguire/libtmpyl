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
#ifndef TMPYL_MOD_360_METHOD_H
#define TMPYL_MOD_360_METHOD_H
#define TMPYL_MOD_360_METHOD                                                   \
{                                                                              \
    "mod_360",                                                                 \
    tmpyl_mod_360,                                                             \
    METH_VARARGS,                                                              \
    "\r\t"                                                                     \
    "Function:\n\r\t\t"                                                        \
    "tmpyl.mod_360\n\r\t"                                                      \
    "Purpose:\n\r\t\t"                                                         \
    "Compute the remainder after division of the input by 360."                \
    "\n\r\tArguments\n\r\t\t"                                                  \
    "x:\n\r\t\t\t"                                                             \
    "Independent variable for |x|. Allowed inputs are int,\n\r\t\t\t"          \
    "float, list (of ints and floats),\n\r\t\t\t"                              \
    "and numpy arrays (if tmpyl was built with numpy support).\n\r\t"          \
    "Outputs:\n\r\t\t"                                                         \
    "x_mod_360:\n\r\t\t\t"                                                     \
    "The remainder of x after division by 360. Same type as input.\n\r\t"      \
    "Example:\n\r\t\t"                                                         \
    ">>> import numpy\n\r\t\t"                                                 \
    ">>> import tmpyl\n\r\t\t"                                                 \
    ">>> x = numpy.arange(0,100,0.01)\n\r\t\t"                                 \
    ">>> y = tmpyl.mod_360(x)"                                                 \
}
#endif
