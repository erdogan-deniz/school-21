"""Sphinx configuration for data_science/project_01.

Autodoc reads docstrings off ``src/models/`` (TextPreprocessor,
TextToFeaturesConverter) and ``src/utilities/`` (handle_errors
decorator, top_similar_vectors). Theme + extensions mirror the
canonical python/bootcamp/old/day_07 setup so all Sphinx subprojects
render identically on the unified Pages site.

The model loads inside ``initialize_tools()`` (spaCy en_core_web_lg,
SymSpell dictionary, Word2Vec) make autodoc import-time heavy on a
fresh CI runner; we manage that in pages.yml by installing
``requirements.txt`` before ``make html`` and not pre-importing
the heavy modules at conf-time.
"""

import os
import sys

# Place ``src/`` on sys.path so absolute imports work the same way
# Sphinx sees them at autodoc time as the runtime does. Mirrors what
# text_preprocessor.py / text_features_converter.py do themselves.
sys.path.insert(0, os.path.abspath("../../src"))

# -- Project information -----------------------------------------------------
project = 'data_science/project_01 — "Tweets" NLP'
copyright = "2026, Deniz Erdogan"
author = "Deniz Erdogan"
release = "0.1"

# -- General configuration ---------------------------------------------------
extensions = [
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",  # tolerate Google / NumPy / RST-list docstrings
    "sphinx.ext.viewcode",  # link rendered API to source
]

templates_path = ["_templates"]
exclude_patterns = []

# Don't fail the build if autodoc can't import a heavy model dependency
# (spaCy / gensim / nltk) — surface the warning but keep going so the
# rest of the docs render.
autodoc_mock_imports = ["spacy", "gensim", "nltk", "symspellpy", "sklearn"]

# -- Options for HTML output -------------------------------------------------
html_theme = "furo"
html_static_path = ["_static"]
