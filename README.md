# libtmpyl
Python wrapper for libtmpl.

# Building
`tmpyl` can be build with or without `numpy` support, but having
`numpy` installed is highly recommended. Various mathematical functions
in `tmpyl` provide support for `numpy` arrays, but this is only available
if `numpy` is installed during build-time.


## Get the source.
Close the repo:
```
git clone https://github.com/ryanmaguire/libtmpyl.git
```
Initialize submodules:
```
git submodule init
git pull --recurse-submodules
```

## Build Instructions (GNU/Linux, FreeBSD, macOS)

### Update pip
```
python3 -m pip install --upgrade pip
```
On certain Linux distributions you may need to add `--break-system-packages`:
```
python3 -m pip install --upgrade pip --break-system-packages
```
If you want to avoid using the `--break-system-packages` flag,
try building in a virtual environment.

### Install `numpy` (optional)
```
python3 -m pip install numpy
```
or
```
python3 -m pip install numpy --break-system-packages
```

### Compile and install
```
python3 -m pip install .
```
As before, some Linux distributions require an additional flag.
```
python3 -m pip install . `--break-system-packages`
```

## Build Instructions (Windows)

### Update pip
Assuming you installed Python from
[https://www.python.org/](https://www.python.org/), you can update via:
```
py -m pip install --upgrade pip
```

### Install `numpy` (optional)
```
py -m pip install numpy
```

### Build and Install
If you are using 64-bit python, make sure you are in a
**64-bit command line** otherwise `libtmpl` will build in 32-bit mode,
and you will have missing symbols when compiling `tmpyl`.
```
py -m pip install .
```
