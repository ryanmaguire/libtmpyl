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
#   Date:       January 18, 2023.                                              #
################################################################################
"""

import sys
import time

# Python 3.6 and up use ModuleNotFoundError. Previously used was ImportError.
if sys.version_info[0] > 2 and sys.version_info[1] > 5:
    MyError = ModuleNotFoundError
else:
    MyError = ImportError

# Check for numpy.
try:
    import numpy
except MyError:
    sys.exit("numpy not installed.")

# Check for tmpyl.
try:
    import tmpyl
except MyError:
    sys.exit("tmpyl not installed.")

# Routine for comparing two functions.
def timetest(start, end, number, func0, func1):

    dx = (end - start)/number
    arr = numpy.arange(start, end, dx)

    t0 = time.time()
    y = func0(arr)
    t1 = time.time()
    print("tmpyl: %f" % (t1-t0))

    t0 = time.time()
    y = func1(arr)
    t1 = time.time()
    print("other: %f" % (t1-t0))

    # Get the error.
    y = func0(arr)
    z = func1(arr)

    # Print the results.
    ind = numpy.where(z != 0)
    y = y[ind]
    z = z[ind]
    k = (y - z)/z
    print("max rel error: %e" % numpy.max(numpy.abs(k)))
    print("rms rel error: %e" % numpy.sqrt(numpy.mean(numpy.square(k))))
