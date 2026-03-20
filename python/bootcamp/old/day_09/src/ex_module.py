# Necessary functions for setup:
from distutils.core import setup
from Cython.Build import cythonize

# Setup new module:
setup(ext_modules = cythonize("multiply.pyx"))
