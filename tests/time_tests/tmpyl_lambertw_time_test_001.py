"""
################################################################################
#                                   LICENSE                                    #
################################################################################
#   This file is part of libtmpyl.                                             #
#                                                                              #
#   libtmpyl is free software: you can redistribute it and/or modify it        #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpyl is distributed in the hope that it will be useful,                #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpyl.  If not, see <https://www.gnu.org/licenses/>.         #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       October 31, 2022.                                              #
################################################################################
"""
# pylint: disable=E1101
import scipy.special as sf
import tmpyl
import timetest

def lambertw(x_val):
    """
        Computes W(x) for real x.
    """
    return sf.lambertw(x_val).real

timetest.timetest(-0.3, 4.0, int(1E7), tmpyl.lambertw, lambertw)
