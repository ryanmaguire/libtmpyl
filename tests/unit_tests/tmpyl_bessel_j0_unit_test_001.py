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
#   Date:       January 28, 2022.                                              #
################################################################################
"""

# pylint: disable = c-extension-no-member, invalid-name
import sys
import tmpyl

# Allowed error for function.
EPS = 1.0E-16

# The function we're testing.
FUNC = tmpyl.bessel_j0

# The value at zero.
VAL = 1.0

# Python 2 has long, python 3 does not.
if sys.version_info[0] > 2:
    long = int

# Can this function handle integers correctly?
if abs(FUNC(int(0)) - VAL) > EPS:
    sys.exit("FAIL: Int")

# What about long?
if abs(FUNC(long(0)) - VAL) > EPS:
    sys.exit("FAIL: Long")

# Float?
if abs(FUNC(float(0)) - 1.0) > EPS:
    sys.exit("FAIL: Float")

# Lists?
err = [abs(y - VAL) for y in FUNC([int(0), long(0), float(0)])]
if max(err) > EPS:
    sys.exit("FAIL: List")

print("PASS")
