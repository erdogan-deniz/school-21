"""Sphinx configuration for python/bootcamp/new/day_01.

Autodoc reads docstrings off `src/utils.py` and the `src/models/`
package. Theme + extensions mirror the canonical day_07 setup so the
two pages render with the same look-and-feel on the unified Pages
site.
"""

import os
import sys

# -- Path setup --------------------------------------------------------------
# autodoc imports the documented modules at build time, so they must
# be importable. The package layout is `src/<package>/` with
# `pyproject.toml` declaring `[tool.setuptools.packages.find] where =
# ["src"]`, hence we add `src/` to sys.path.
sys.path.insert(0, os.path.abspath("../../src"))

# -- Project information -----------------------------------------------------
project = "day-01 (new)"
copyright = "2026, Deniz Erdogan"
author = "Deniz Erdogan"
release = "0.1"

# -- General configuration ---------------------------------------------------
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",  # tolerate Google / NumPy-style docstrings
    "sphinx.ext.viewcode",  # link rendered docs to source
]

templates_path = ["_templates"]
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
html_theme = "furo"
html_static_path = ["_static"]
