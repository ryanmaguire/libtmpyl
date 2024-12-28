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

import unittests

def fresnel_cos(x_val):
    """
        Function:
            fresnel_cos
        Purpose:
            Computes the normalized Fresnel cosine function.
        Arguments:
            x_val:
                The independent variable. A real number.
        Output:
            C_x:
                The normalized Fresnel Cosine evaluated at x.
        Method:
            Use the complex error function
            formula for the Fresnel functions.
    """
    pi_factor = unittests.mpmath.sqrt(unittests.mpmath.pi()) / 2
    plus_scale = unittests.mpmath.mpc(1 + 1j)
    minus_scale = unittests.mpmath.mpc(1 - 1j)
    factor = unittests.mpmath.mpf(x_val) * pi_factor
    left = minus_scale * unittests.mpmath.erf(plus_scale * factor)
    right = plus_scale * unittests.mpmath.erf(minus_scale * factor)
    return (left + right).real / 4
