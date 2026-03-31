PYTHON      = python3
SRC_DIR     = src
HOME        ?= $(USERPROFILE)
INSTALL_DIR ?= $(HOME)/.local/maze

.PHONY: all install install-dev uninstall run web \
        tests test cov coverage lint format \
        dvi dist clean help

# ──────────────────────────────────────────────────────────────────────────────
# Default
# ──────────────────────────────────────────────────────────────────────────────

all: install

# ──────────────────────────────────────────────────────────────────────────────
# Installation
# ──────────────────────────────────────────────────────────────────────────────

install:
	pip install .
	$(PYTHON) -c "import os; os.makedirs(r'$(INSTALL_DIR)', exist_ok=True)"
	$(PYTHON) -c "import shutil; shutil.copytree('$(SRC_DIR)', r'$(INSTALL_DIR)', dirs_exist_ok=True)"
	$(PYTHON) -c "import shutil; shutil.copytree('data', r'$(INSTALL_DIR)/data', dirs_exist_ok=True)"
	$(PYTHON) -c "import shutil; shutil.copytree('assets', r'$(INSTALL_DIR)/assets', dirs_exist_ok=True)"
	$(PYTHON) -c "print(r'Installed to $(INSTALL_DIR)')"

install-dev:
	pip install ".[dev]"

uninstall:
	pip uninstall -y Maze
	$(PYTHON) -c "import shutil; shutil.rmtree(r'$(INSTALL_DIR)', ignore_errors=True)"
	$(PYTHON) -c "print(r'Uninstalled from $(INSTALL_DIR)')"

# ──────────────────────────────────────────────────────────────────────────────
# Run
# ──────────────────────────────────────────────────────────────────────────────

run:
	cd $(SRC_DIR) && $(PYTHON) main.py

web:
	cd $(SRC_DIR) && uvicorn web.server:app --host 0.0.0.0 --port 8080 --reload

# ──────────────────────────────────────────────────────────────────────────────
# Tests & coverage
# ──────────────────────────────────────────────────────────────────────────────

tests:
	$(PYTHON) -m pytest

test: tests

cov:
	$(PYTHON) -m pytest --cov=$(SRC_DIR) --cov-report=term-missing

coverage: cov

# ──────────────────────────────────────────────────────────────────────────────
# Linting & formatting
# ──────────────────────────────────────────────────────────────────────────────

lint:
	$(PYTHON) -m ruff check $(SRC_DIR) tests

format:
	$(PYTHON) -m ruff format $(SRC_DIR) tests

# ──────────────────────────────────────────────────────────────────────────────
# Distribution
# ──────────────────────────────────────────────────────────────────────────────

dvi:
	$(PYTHON) -c "print('Documentation: see README.md and docs/')"

dist:
	tar -czf maze_dist.tar.gz \
	    $(SRC_DIR) data assets tests docs \
	    pyproject.toml Makefile README.md

# ──────────────────────────────────────────────────────────────────────────────
# Cleanup
# ──────────────────────────────────────────────────────────────────────────────

clean:
	$(PYTHON) -c "import shutil,pathlib;[shutil.rmtree(p,True) for t in('__pycache__','.pytest_cache','.ruff_cache','.mypy_cache') for p in pathlib.Path('.').rglob(t)]"
	$(PYTHON) -c "import pathlib;[p.unlink(missing_ok=True) for p in pathlib.Path('.').rglob('*.pyc')]"
	$(PYTHON) -c "import pathlib;[p.unlink(missing_ok=True) for p in pathlib.Path('.').rglob('.coverage*') if p.is_file()]"
	$(PYTHON) -c "import shutil,pathlib;[shutil.rmtree(d,True) for d in('htmlcov','build','dist')]+[shutil.rmtree(p,True) for p in pathlib.Path('.').rglob('*.egg-info') if p.is_dir()]"
	$(PYTHON) -c "import pathlib;[p.unlink(missing_ok=True) for p in[pathlib.Path('maze_dist.tar.gz'),pathlib.Path('output.png'),pathlib.Path('coverage.xml'),pathlib.Path('cov.xml')]]"

# ──────────────────────────────────────────────────────────────────────────────
# Help
# ──────────────────────────────────────────────────────────────────────────────

help:
	$(PYTHON) -c "print('\n'.join(['Available targets:','  install      Install runtime dependencies and copy files to INSTALL_DIR','  install-dev  Install all dependencies including dev tools','  uninstall    Remove installed files and runtime dependencies','  run          Launch the desktop GUI','  web          Launch the FastAPI web server','  tests        Run the test suite','  test         Alias for tests','  cov          Run tests with coverage report','  coverage     Alias for cov','  lint         Check code with ruff (src + tests)','  format       Format code with ruff (src + tests)','  dvi          Show documentation pointer','  dist         Create a release tarball','  clean        Remove all build and cache artefacts']))"
