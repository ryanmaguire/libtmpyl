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

import numpy
import tmpyl
import timetest

# Numpy cosd equivalent.
def cosd(x_val):
    """
        Computes cosine in degrees.
    """
    return numpy.cos(numpy.deg2rad(numpy.mod(x_val, 360.0)))

timetest.timetest(0.0, 1.0E100, int(1E8), tmpyl.cosd, cosd)
