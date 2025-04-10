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
import mpmath_normalized_fresnel_cos

START = 2**37 - 5.0
END = 2**37 + 5.0
NUMBER = int(1E4)
FUNC0 = tmpyl.normalized_fresnel_cos
FUNC1 = mpmath_normalized_fresnel_cos.fresnel_cos
unittests.unittest(START, END, NUMBER, FUNC0, FUNC1)
