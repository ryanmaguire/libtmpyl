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

# pylint: disable = c-extension-no-member
import sys
import tmpyl

# Allowed error for function.
EPS = 1.0E-16

# The function we're testing.
FUNC = tmpyl.bessel_j0

# The value at zero.
VAL = 1.0

# ImportError became ModuleNotFoundError in Python 3.6. Check the version first.
if sys.version_info[0] > 2 and sys.version_info[1] > 5:

    # If numpy is not available, we'll specify this with the macro
    # TMPYL_HAS_NUMPY by setting it to zero.
    try:
        import numpy
    except ModuleNotFoundError:
        sys.exit("numpy is not installed.")

# For older versions, use ImportError.
else:

    # Again, check if numpy is available.
    try:
        import numpy
    except ImportError:
        sys.exit("numpy is not installed.")

# Can bessel_j0 handle arrays of floats?
if max(abs(FUNC(numpy.zeros(10)) - VAL)) > EPS:
    sys.exit("FAIL: Array of Zeros")

print("PASS")
