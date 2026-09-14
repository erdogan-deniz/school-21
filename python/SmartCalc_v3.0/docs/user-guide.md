# SmartCalc v3.0 — User Guide

## Overview

SmartCalc v3.0 is a desktop calculator application with three modules:

- **Calculator** — arithmetic expressions, scientific functions, variable *x*, and function graphing
- **Loan** — annuity and differentiated payment schedules
- **Deposit** — interest accrual with capitalization, tax, additions, and withdrawals

The GUI is built with PyQt6. Calculation logic is backed by a compiled C shared library.

---

## Prerequisites

| Platform | Requirement |
|----------|-------------|
| All | Python 3.11 |
| All | PyQt6, matplotlib (installed automatically) |
| Windows | Visual Studio Build Tools with MSVC v14x and Windows 10/11 SDK |
| Linux / macOS | GCC or Clang, `make` |

---

## Installation

### From source

```bash
git clone <repo-url>
cd python_smart_calc

# Create virtual environment and install dependencies
python3.11 -m venv .venv
source .venv/bin/activate        # Windows: .venv\Scripts\activate

pip install -e ".[dev]"

# Build the C shared library
make lib                         # Linux / macOS
# Windows (PowerShell):
python scripts/build_lib.py

# Run the application
make run
```

### Pre-built binary (Windows)

Run the `SmartCalc-Setup.exe` installer. No Python or build tools required.

---

## Configuration

Settings are read from `src/config.ini` on startup. Edit the file with any text editor and restart the application.

```ini
[display]
theme       = light       # light | dark
font_size   = 14          # integer, 6–72 pt
precision   = 7           # decimal digits shown, 1–15

[logging]
rotation_period = day     # hour | day | month
```

All values are optional — missing keys fall back to the defaults shown above.

---

## Calculator

### Entering expressions

Type an expression in the input field and press **=** or **Enter**.

- Maximum input length: **255 characters**
- Use `x` as a variable (its value is set in the *x =* field below the display)
- Scientific notation is accepted: `1e5`, `2.5e-3`, `1E+10`

### Supported operators

| Operator | Meaning | Example |
|----------|---------|---------|
| `+` `-` `*` `/` | Basic arithmetic | `3 + 4 * 2` |
| `^` | Power | `2^10` |
| `mod` | Modulo | `10 mod 3` |
| `( )` | Grouping | `(1 + 2) * 3` |

Unary minus and plus are supported: `-x`, `+3.14`.

### Supported functions

| Function | Description |
|----------|-------------|
| `sin(x)` | Sine (radians) |
| `cos(x)` | Cosine (radians) |
| `tan(x)` | Tangent (radians) |
| `asin(x)` | Arcsine |
| `acos(x)` | Arccosine |
| `atan(x)` | Arctangent |
| `sqrt(x)` | Square root |
| `ln(x)` | Natural logarithm |
| `log(x)` | Base-10 logarithm |

### Examples

```
sin(x) + cos(x)
sqrt(2^8)
ln(2.718281828)
(3 + 4) mod 5 * 2
```

---

## Graph

Switch to the **Graph** tab to plot a function of *x*.

1. Enter an expression containing `x` in the input field (Calculator tab)
2. Open the **Graph** tab
3. Set the x-axis range using the **x min** / **x max** spin boxes
4. Click **Plot** (or press Enter)

Y-values outside ±1,000,000 are treated as discontinuities and rendered as gaps.

---

## Loan Calculator

Switch to the **Loan** tab.

### Input fields

| Field | Description |
|-------|-------------|
| Total amount | Loan principal (must be > 0) |
| Term (months) | Repayment period in months (must be > 0) |
| Interest rate | Annual rate in percent (must be > 0) |
| Payment type | Annuity or Differentiated |

### Payment types

**Annuity** — equal monthly payments throughout the term.
Result: monthly payment, total overpayment, total amount repaid.

**Differentiated** — decreasing payments: fixed principal portion plus accruing interest.
Result: first (largest) payment, last (smallest) payment, total overpayment, total amount repaid.

---

## Deposit Calculator

Switch to the **Deposit** tab.

### Input fields

| Field | Description |
|-------|-------------|
| Deposit amount | Initial balance (must be > 0) |
| Term (months) | Duration in months (must be > 0) |
| Interest rate | Annual rate in percent (must be > 0) |
| Tax rate | Tax on interest income, percent (0–100) |
| Payment period | Monthly, quarterly, or annually |
| Capitalization | If enabled, accrued interest is added to balance (compound interest) |
| Additions | Scheduled deposits: month number and amount |
| Withdrawals | Scheduled withdrawals: month number and amount |

### Results

| Field | Description |
|-------|-------------|
| Accrued interest | Gross interest earned over the term |
| Tax amount | Tax withheld on interest income |
| Final amount | Closing balance (principal + net interest) |

---

## History

The **History** tab shows the 100 most recent calculations. Up to 1,000 entries are stored persistently in a local SQLite database:

- **Windows:** `%APPDATA%\smartcalc_v3\history.db`
- **Linux / macOS:** `~/.smartcalc_v3/history.db`

Click any entry to load its expression back into the calculator input field.

---

## Logging

Log files are written to the `logs/` directory inside the application folder.

- The active log is always named `smartcalc.log`
- Rotated files are named by date: `2026-04-01.log` (daily), `2026-04-01_14.log` (hourly)
- Up to 30 rotated files are retained

The rotation period is set by `rotation_period` in `config.ini`.

---

## Troubleshooting

**"Shared library not found" on startup**
The C library `src/libs/libsmartcalc.dll` (or `.so` / `.dylib`) is missing. Run `make lib` (or `python build_lib.py` on Windows) to build it.

**Graph is empty or shows no curve**
Check that the expression contains `x` and that the x-axis range is valid (min < max).

**Result shows NaN**
The expression is mathematically invalid (e.g. `sqrt(-1)`, division by zero, unbalanced parentheses).

**Wrong theme or font after editing config.ini**
The configuration is read once at startup — restart the application after editing.
