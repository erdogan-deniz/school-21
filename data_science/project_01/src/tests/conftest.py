"""Shared pytest configuration for data_science/project_01.

The project keeps its packages under ``src/models`` and
``src/utilities``. Tests live one level down at ``src/tests``, so we
need ``src/`` on ``sys.path`` for absolute imports like
``from models.text_preprocessor import TextPreprocessor`` to work.

This mirrors what ``text_preprocessor.py`` itself does at module
import time (it manipulates ``sys.path`` to find ``utilities``), so
the test environment matches the runtime one.
"""

import os
import sys

sys.path.insert(
    0,
    os.path.abspath(os.path.join(os.path.dirname(__file__), "..")),
)
