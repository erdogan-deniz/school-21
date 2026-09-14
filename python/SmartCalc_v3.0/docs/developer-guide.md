# SmartCalc v3.0 — Developer Guide

## Architecture

SmartCalc follows the **MVVM** (Model–View–ViewModel) pattern strictly:

```text
┌─────────────────────────────────────────────┐
│  View  (src/view/)                          │
│  PyQt6 widgets — zero business logic        │
│  Reads ViewModel properties, emits signals  │
└─────────────────────┬───────────────────────┘
                      │ Qt signals / properties
┌─────────────────────▼───────────────────────┐
│  ViewModel  (src/viewmodel/)                │
│  QObject subclasses — owns UI state         │
│  No widget imports, no direct model access  │
│  from View                                  │
└─────────────────────┬───────────────────────┘
                      │ plain Python calls
┌─────────────────────▼───────────────────────┐
│  Model  (src/model/)                        │
│  Pure Python — no Qt imports                │
│  Wraps C shared library via ctypes          │
└─────────────────────────────────────────────┘
```

**Rule:** Model classes must never import Qt. View classes must never call Model methods directly.

---

## Project Structure

```text
python_smart_calc/
├── src/
│   ├── main.py               # Entry point: wires all layers, starts event loop
│   ├── config.ini            # Runtime configuration (theme, precision, logging)
│   ├── libs/                 # Compiled C shared library
│   │   ├── libsmartcalc.dll  # Windows
│   │   ├── libsmartcalc.so   # Linux
│   │   └── libsmartcalc.dylib# macOS
│   ├── model/                # Business logic (no Qt)
│   │   ├── calculator.py     # ctypes wrapper for expression evaluation
│   │   ├── loan.py           # Annuity / differentiated loan calculations
│   │   ├── deposit.py        # Deposit interest with capitalization
│   │   ├── history.py        # SQLite-backed calculation history
│   │   ├── finance_base.py   # Shared validation for Loan and Deposit
│   │   ├── lib_loader.py     # Cross-platform .dll/.so/.dylib loader
│   │   ├── results.py        # TypedDict result types
│   │   └── enums.py          # PaymentType, AccrualPeriod
│   ├── viewmodel/            # Presentation logic (Qt signals, no widgets)
│   │   ├── calc_viewmodel.py
│   │   ├── loan_viewmodel.py
│   │   ├── deposit_viewmodel.py
│   │   └── signal.py
│   ├── view/                 # PyQt6 widgets
│   │   ├── main_window.py    # Tabbed main window
│   │   ├── calc_widget.py    # Expression input and button grid
│   │   ├── graph_widget.py   # matplotlib graph embedded in Qt
│   │   ├── loan_widget.py    # Loan form and results
│   │   ├── deposit_widget.py # Deposit form and results
│   │   ├── history_widget.py # History list view
│   │   ├── help_dialog.py    # Help / about dialog
│   │   ├── base_widget.py    # Shared error display base class
│   │   └── styles.qss        # Qt stylesheets (light / dark themes)
│   └── utils/
│       ├── config.py         # Reads config.ini with validation and defaults
│       └── logger.py         # Rotating file log handler setup
├── tests/
│   ├── conftest.py           # Shared pytest fixtures
│   ├── model/                # Unit tests for Model layer
│   ├── viewmodel/            # Unit tests for ViewModel layer
│   ├── utils/                # Tests for config and logger utilities
│   ├── integration/          # Cross-layer integration tests
│   └── property_based/       # Hypothesis property-based tests
├── docs/                     # Project documentation
├── content/                  # Images and media assets
├── scripts/                  # Build helpers and packaging specs
├── Makefile                  # Build, test, run, dist targets
└── pyproject.toml            # Project metadata and tool configuration
```

---

## Development Setup

```bash
git clone <repo-url>
cd python_smart_calc

python3.11 -m venv .venv
source .venv/bin/activate      # Windows: .venv\Scripts\activate

pip install -e ".[dev]"
```

Place the C sources at `smart_calculator/src/` (copy from the original project), then build the library:

```bash
make lib                      # Linux / macOS — requires GCC
python scripts/build_lib.py   # Windows — requires MSVC Build Tools
```

---

## Building the C Library

### Windows (MSVC)

`build_lib.py` auto-discovers the latest Visual Studio Build Tools via `vswhere.exe` and compiles all `.c` source files into `src/libs/libsmartcalc.dll`.

```powershell
python scripts/build_lib.py
```

The object cache lives in `build/obj/`. Delete it to force a full recompile:

```bash
rm -rf build/obj/
python scripts/build_lib.py
```

### Linux / macOS (GCC)

```bash
make lib
```

The Makefile uses:

```bash
gcc -shared -fPIC -std=c11 -lm <sources> -o src/libs/libsmartcalc.so
```

### C source location

The build system looks for C sources in this order:

1. `SMARTCALC_C_SRC` environment variable
2. `smart_calculator/src/` — local copy placed alongside the Python project
3. `c_src/` — git submodule fallback

---

## Running Tests

```bash
make test                         # run all tests
.venv/Scripts/python -m pytest    # equivalent, explicit venv

# With coverage
pytest --cov=src --cov-report=html

# One test file
pytest tests/model/test_calculator.py -v

# One test class or function
pytest tests/model/test_calculator.py::TestCalculator::test_basic -v
```

### Test layout

| Directory               | What it covers                                                  |
|-------------------------|-----------------------------------------------------------------|
| `tests/model/`          | Calculator, LoanCalculator, DepositCalculator, History, enums   |
| `tests/viewmodel/`      | ViewModel state transitions and signal emissions                |
| `tests/utils/`          | AppConfig parsing, logger setup                                 |
| `tests/integration/`    | Model + ViewModel wired together end-to-end                     |
| `tests/property_based/` | Hypothesis randomised tests for calculator and finance models   |

---

## Code Quality

```bash
# Linting and formatting
ruff check src tests
ruff format src tests

# Type checking
mypy src
```

Key rules enforced by ruff: `E/F/W` (pycodestyle/pyflakes), `I` (import order), `D` (docstrings), `N` (naming), `ANN` (type annotations), `B` (bugbear), `SIM`, `RET`, `UP`.

Line length: **80 characters**. Target: **Python 3.11**.

---

## Distribution

### PyInstaller binary

```bash
make lib       # build DLL first
make dist      # produces dist/SmartCalc/
```

The spec file `smartcalc.spec` bundles `libsmartcalc.dll` as a binary and `config.ini` as data. The output is a one-folder distribution at `dist/SmartCalc/`.

### Windows installer (Inno Setup)

After `make dist`, open `scripts/installer.iss` with [Inno Setup](https://jrsoftware.org/isinfo.php) and compile, or run:

```bash
iscc scripts/installer.iss
```

---

## Cross-Platform Notes

### ctypes float type

MSVC compiles `long double` as 64-bit `double`; GCC uses 80-bit extended. The `Calculator` class selects the correct ctypes type automatically:

```python
float_type = ctypes.c_double if os.name == "nt" else ctypes.c_longdouble
```

### History database path

| Platform      | Path                                  |
|---------------|---------------------------------------|
| Windows       | `%APPDATA%\smartcalc_v3\history.db`   |
| Linux / macOS | `~/.smartcalc_v3/history.db`          |

### Python version

Exactly **Python 3.11** is required (`pyproject.toml`: `>=3.11, <3.12`). The `StrEnum` class used for `PaymentType` and `AccrualPeriod` was added in 3.11.

---

## Extending the Application

### Adding a new calculator tab

1. Create `src/model/my_model.py` — pure Python, no Qt imports.
2. Create `src/viewmodel/my_viewmodel.py` — subclass `QObject`, emit signals, call the model.
3. Create `src/view/my_widget.py` — subclass the appropriate base, connect to ViewModel signals.
4. Register the tab in `src/view/main_window.py`.
5. Instantiate and wire everything in `src/main.py`.
6. Add tests in `tests/model/test_my_model.py`.

### Adding a new C function

1. Implement and export the function in the C project.
2. Rebuild the shared library (`make lib` or `python scripts/build_lib.py`).
3. Add the export to the `build_lib.py` linker flags (`/EXPORT:my_func`).
4. Declare the `argtypes` / `restype` in the relevant Model class.
5. Write a Python wrapper method with validation and error handling.
