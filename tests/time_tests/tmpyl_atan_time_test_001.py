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

import sys

# Python 3.6 and up use ModuleNotFoundError. Previously used was ImportError.
if sys.version_info[0] > 2 and sys.version_info[1] > 5:
    MyError = ModuleNotFoundError
else:
    MyError = ImportError

# Check if tmpyl is installed. It should be if running this test.
try:
    import tmpyl
except MyError:
    sys.exit("FAIL: tmpyl not installed")

# Check for timeit.
try:
    import timeit
except MyError:
    sys.exit("timeit not installed.")

# Check for numpy.
try:
    import numpy
except MyError:
    sys.exit("numpy not installed.")

# The Array being tested.
ARR = numpy.arange(-10.0, 10.0, 0.0001)

# The two functions being compared.
FUNC0 = tmpyl.atan
FUNC1 = numpy.arctan

# The number of iterations of the test.
N = int(1E2)

# Run the first time test.
time0 = timeit.timeit(
    setup = "from __main__ import FUNC0, ARR",
    stmt = "y = FUNC0(ARR)",
    number = N
)

# Run the second time test.
time1 = timeit.timeit(
    setup = "from __main__ import FUNC1, ARR",
    stmt = "z = FUNC1(ARR)",
    number = N
)

# Get the error.
y = FUNC0(ARR)
z = FUNC1(ARR)

# Print the results.
print("tmpyl:         %f" % time0)
print("numpy:         %f" % time1)
print("max rel error: %e" % numpy.max(numpy.abs((y - z)/z)))
print("rel rel error: %e" % numpy.sqrt(numpy.mean(numpy.square((y - z)/z))))
