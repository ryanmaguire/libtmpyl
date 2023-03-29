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
#   Date:       January 11, 2023.                                              #
################################################################################
"""

import numpy
import tmpyl
import timetest

def mod_360(x_val):
    """
        Computes the argument mod 360.
    """
    return numpy.fmod(x_val, 360)

timetest.timetest(0.5, 1.0E50, int(1E8), tmpyl.mod_360, mod_360)
