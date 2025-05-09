"""
################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify it         #
#   under the terms of the GNU General Public License as published by          #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Purpose:                                                                   #
#       This file builds tmpyl, the Python Extension module for libtmpl.       #
#       tmpyl is built using the Python-C API and no python code is            #
#       used, other than this setup.py file. Because of this I can only        #
#       guarantee tmpyl will build with CPython. That is, I've never tested    #
#       it with PyPy or the other implementations of the Python language.      #
#   Notes:                                                                     #
#       tmpyl builds with both Python 2 and Python 3. There are macros inside  #
#       the C source files to check which python version is being used. There  #
#       is also support for numpy arrays. If you do not have numpy installed,  #
#       tmpyl will still build. If you later install numpy, but built tmpyl    #
#       without numpy support, none of the functions will be able to accept    #
#       numpy arrays as arguments. It is highly recommended to build tmpyl     #
#       with numpy support since those tools are very convenient.              #
################################################################################
#   Author: Ryan Maguire                                                       #
#   Date:   August 31, 2021.                                                   #
################################################################################
"""

# Python is swapping distutils with setuptools.
try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

import subprocess
import site
import sys
import os

# For reasons beyond me, on Windows and macOS the site_packages directory is
# occasionally not included in the Python PATH. This is probably related to
# how the user installed Python (Did they use the Windows Store? The Python
# website? macOS developer tools? homebrew?). On FreeBSD and Linux the issue
# only appears if running in a virtual environment (i.e. python -m venv ...).
# Adding the site_packages directory to the systme path fixes the issue.
for site in site.getsitepackages():
    sys.path.append(site)

# ImportError became ModuleNotFoundError in Python 3.6. Check the version first.
if sys.version_info[0] > 2 and sys.version_info[1] > 5:

    # If numpy is not available, we'll specify this with the macro
    # TMPYL_HAS_NUMPY by setting it to zero.
    try:
        import numpy
        include = [numpy.get_include()]
        tmpyl_macros=[("TMPYL_HAS_NUMPY", 1)]
    except ModuleNotFoundError:
        include = []
        tmpyl_macros = [("TMPYL_HAS_NUMPY", 0)]

# For older versions, use ImportError.
else:

    # Again, check if numpy is available.
    try:
        import numpy
        include = [numpy.get_include()]
        tmpyl_macros = [("TMPYL_HAS_NUMPY", 1)]
    except ImportError:
        include = []
        tmpyl_macros = [("TMPYL_HAS_NUMPY", 0)]



if os.name == "nt":
    include.append(".\\")
    os.chdir(".\\libtmpl")
    subprocess.call(["make.bat"])
    libs = [".\\libtmpl\\libtmpl.lib"]
    os.chdir("..\\")

else:
    include.append("./")
    os.chdir("./libtmpl/")
    subprocess.call(["make", "-j", "BUILD_STATIC=1"])
    libs = ["./libtmpl/libtmpl.a"]
    os.chdir("../")


# List of files to be compiled for tmpyl.
srclist = []

for file in os.listdir("src/"):

    # Only add .c files.
    if file[-1] == "c":
        srclist.append("src/%s" % file)

# Optional arguments for the compiler.
optional_args = []

# Create the module.
setup(
    name = 'tmpyl',
    version = '0.1',
    description = 'Python Extension Module for the C Library libtmpl',
    author = 'Ryan Maguire',
    ext_modules = [
          Extension(
            'tmpyl',
            srclist,
            extra_compile_args = optional_args,
            define_macros = tmpyl_macros,
            include_dirs = include,
            extra_objects = libs
        )
    ]
)
