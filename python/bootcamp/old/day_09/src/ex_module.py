# Necessary functions for setup:
from Cython.Build import cythonize
from distutils.core import setup

# Setup new module:
setup(ext_modules=cythonize("multiply.pyx"))
