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
#   Date:       December 28, 2024                                              #
################################################################################
"""

# pylint: disable = too-many-arguments
import sys

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

# Check for mpmath.
try:
    import mpmath
except MyError:
    sys.exit("mpmath not installed.")

# By setting the precision to more than 1074 = 1023 + 51 bits, a value that
# is less than 2^(-1074) will truncate to zero when we cast an mpmath.mpf
# object to a float. Some functions, like sinpi or cospi, use look-up tables
# to ensure something like sinpi(1) = 0, exactly. No matter how many bits of
# pi one uses, naively doing sin(pi) will not result in zero. The relative
# error is hence infinite (or undefined). This truncation trick means we will
# get the correct answer once we round to float.
#   mpmath.mp.prec = 1080

# 224 bits (octuple precision) is usually more than enough.
mpmath.mp.prec = 224

def relative_error(answer, data):
    """
        Computes the relative error, |(answer - data) / answer|.
    """

    length = len(answer)
    difference = [float(answer[ind] - data[ind]) for ind in range(length)]
    return [abs(float(difference[ind]/answer[ind])) for ind in range(length)]

def rms(array):
    """
        Computes the root-mean-square of an array.
    """
    return numpy.sqrt(numpy.mean(numpy.square(array)))

# Routine for comparing two functions.
def unittest(start, end, number, func0, func1, toler = 2**-50):
    """
        Function:
            unittest
        Purpose:
            Compares the accuracy of two (hopefully identical) functions.
        Arguments:
            start (float):
                The left end-point of the interval that is tested.
            end (float):
                The right end-point.
            number (int):
                The number of samples to try.
            func0 (function):
                Function object for the first function tested (from tmpyl).
            func1 (function):
                Function that func0 is compared against.
        Outputs:
            None.
    """
    arr = list(numpy.arange(start, end, (end - start) / number))

    # tmpyl functions can handle lists.
    tmpyl_arr = func0(arr)

    # mpmath cannot.
    other_arr = [func1(var) for var in arr]

    # Print the results.
    rel_err = relative_error(other_arr, tmpyl_arr)
    max_rel_err = max(rel_err)
    rms_rel_err = rms(rel_err)

    print(f'max rel error: {max_rel_err}')
    print(f'rms rel error: {rms_rel_err}')

    if max_rel_err < toler:
        print("PASS")
    else:
        print("FAIL")
