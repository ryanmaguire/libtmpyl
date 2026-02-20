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

import os
import site
import platform
import subprocess
import shutil
import sys

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

# Add libtmpl to the include path.
include.append("." + os.sep)

# Check if OpenMP support has been requested.
USE_OPENMP = os.environ.get('USE_OPENMP') == '1'

# List of files to be compiled for tmpyl.
srclist = []

def add_directory(directory):
    """
        Function for adding all of the C files in a
        given directory to the list of files to be compiled.
    """
    full_path = f'src/{directory}/'
    for file in os.listdir(full_path):
        if file[-1] == "c":
            srclist.append(f'{full_path}{file}')

def openmp_args():
    """
        Returns the list of arguments needed by
        the C compiler to enable OpenMP support.
    """
    if not USE_OPENMP:
        return [], []

    # Microsoft's MSVC compiler supports OpenMP 2.0.
    if os.name == "nt":
        return ["/openmp"], []

    # OpenMP support is also possible on macOS (but tricky to set up).
    if platform.system() == "Darwin":

        # The required flags for Apple's clang and GCC differ.
        c_compiler = os.environ.get("CC", "")

        # GCC on macOS does not need -Xpreprocessor. Adding it breaks the
        # linker when building with OpenMP support.
        if "gcc" in c_compiler:
            return ["-fopenmp"], ["-fopenmp"]

        # Apple's Clang on macOS requires -Xpreprocessor. Omiting results
        # in an "unsupported option: -fopenmp" error. We also need to add
        # the path to libomp. The user should specify this directly using
        # export CPATH="...". Use brew --prefix as a fallback if this is
        # not set.
        lflag = "-L" + os.environ.get("CPATH", "$(brew --prefix libomp)/lib")
        return ["-Xpreprocessor", "-fopenmp"], [lflag, "-lomp"]

    # On GNU / Linux, GCC has OpenMP support by default, and LLVM's clang
    # has support as well (but you may need to install libomp to use it).
    return ["-fopenmp"], ["-fopenmp"]

def static_library_paths():
    """
        Compiles libtmpl and returns the
        path to the static library.
    """

    libtmpl = "." + os.sep + "libtmpl"
    build = libtmpl + os.sep + "build"

    # Windows users are required to use CMake. GNU, Linux, FreeBSD, and
    # macOS users may also use CMake.
    if shutil.which("cmake"):

        static = "-DBUILD_SHARED_LIBS=OFF"
        cmake_args = ["cmake", "-S", libtmpl, "-B", build, static]
        command = ["cmake", "--build", build, "--config", "Release", "-j"]

        # Additional flags are needed if OpenMP support is requested.
        if USE_OPENMP:
            cmake_args.append("-DOMP=ON")

        # Run CMake to generate the build files.
        subprocess.run(cmake_args, check = True)

        # Run the build process and compile librssringoccs and libtmpl.
        subprocess.run(command, check=True)

        # Path for Windows users, note the '\' instead of '/'.
        if os.name == "nt":
            return [build + os.sep + "Release" + os.sep + "tmpl.lib"]

        # Path for everyone else.
        return [build + os.sep + "libtmpl.a"]

    # GNU Make is 'gmake' on FreeBSD. Check for this first.
    if shutil.which("gmake"):
        command = ["gmake", libtmpl, "-j", "BUILD_STATIC=1"]

    # GNU Make is simply 'make' on GNU / Linux and macOS.
    elif shutil.which("make"):
        command = ["make", libtmpl, "-j", "BUILD_STATIC=1"]

    else:
        raise RuntimeError("Neither CMake nor GNU Make found. Install one.")

    # gmake and make have nearly identical build steps. The only difference
    # is the name of the command. This is saved in the 'command' variable.
    if USE_OPENMP:
        command.append("OMP=1")

    subprocess.run(command, check = True)
    return [libtmpl + os.sep + "libtmpl.a"]

add_directory(".")
add_directory("wrappers")
add_directory("window_wrappers")

# Optional arguments for the compiler.
static_libraries = static_library_paths()
compile_args, linker_args = openmp_args()

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
            extra_compile_args = compile_args,
            extra_link_args = linker_args,
            define_macros = tmpyl_macros,
            include_dirs = include,
            extra_objects = static_libraries
        )
    ]
)
