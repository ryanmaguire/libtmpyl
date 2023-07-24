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

# Routine for comparing two functions.
def timetest(start, end, number, func0, func1):
    """
        Function:
            timetest
        Purpose:
            Compares the performance of two (hopefully identical) functions.
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

    arr = numpy.arange(start, end, (end - start)/number)

    start_time = time.time()
    tmpyl_arr = func0(arr)
    end_time = time.time()
    print("tmpyl: %f" % (end_time - start_time))

    start_time = time.time()
    other_arr = func1(arr)
    end_time = time.time()
    print("other: %f" % (end_time - start_time))

    # Print the results.
    ind = numpy.where(other_arr != 0)
    tmpyl_arr = tmpyl_arr[ind]
    other_arr = other_arr[ind]
    rel_err = (tmpyl_arr - other_arr)/other_arr
    print("max rel error: %e" % numpy.max(numpy.abs(rel_err)))
    print("rms rel error: %e" % numpy.sqrt(numpy.mean(numpy.square(rel_err))))

def timearr(start, end, step_size, samples, func):
    """
        Function:
            timearr
        Purpose:
            Creates a performance vs. input array for a given function.
        Arguments:
            start (float):
                Starting value of the independent variable.
            end (float):
                Ending value of the independent variable.
            step_size (float):
                The distance between points in the independent variable.
            samples (int):
                The number of samples in the test array used to probe the
                performance of the function between x and x + step_size.
            func (function):
                The function being tested.
        Outputs:
            time_array (list):
                A list of real numbers. The value time_array[ind] corresponds
                to how long func takes to calculate with an input array of
                "samples" many points between start + step_size*ind and
                start + step_size * (ind + 1), in seconds.
    """
    number_of_elements = int((end - start) / step_size)
    out = [0] * number_of_elements

    left = start
    right = start + step_size
    increment = step_size / float(samples)

    for ind in range(number_of_elements):
        x_vals = numpy.arange(left, right, increment)
        start_time = time.time()
        arr = func(x_vals)
        end_time = time.time()
        out[ind] = end_time - start_time
        del arr

    return out
