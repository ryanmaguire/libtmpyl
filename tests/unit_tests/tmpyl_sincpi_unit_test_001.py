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
#   Date:       December 28, 2024.                                             #
################################################################################
"""

# pylint: disable = c-extension-no-member
import tmpyl
import unittests

# Much higher precision needed. See unittests.py for details.
unittests.mpmath.mp.prec = 1080

def sincpi(x_val):
    """
        Computes sinc(pi x) using arbitrary arithemtic (mpmath).
    """
    if x_val == 0:
        return 1

    arg = unittests.mpmath.mpf(x_val) * unittests.mpmath.pi
    return unittests.mpmath.sin(arg) / arg

START = -10
END = 10
NUMBER = int(1E6)
unittests.unittest(START, END, NUMBER, tmpyl.sincpi, sincpi)
