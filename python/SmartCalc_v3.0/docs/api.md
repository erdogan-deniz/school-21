# SmartCalc v3.0 — Python Model API Reference

All public classes live under `src/model/`. They have no Qt dependencies and can be used independently of the GUI.

---

## Calculator

```python
from model.calculator import Calculator
```

Wraps the C shared library (`s21_calculator`) via ctypes.

### Constants

| Name             | Value     | Description                                       |
|------------------|-----------|---------------------------------------------------|
| `MAX_INPUT_LENGTH` | `255`   | Maximum characters accepted by `calculate()`     |
| `GRAPH_Y_LIMIT`  | `1000000` | Y-values outside ±this are treated as gaps       |

### `calculate(expression, x=0.0)`

Evaluate an arithmetic expression.

**Parameters**

| Name         | Type    | Description                              |
|--------------|---------|------------------------------------------|
| `expression` | `str`   | Infix expression, max 255 characters     |
| `x`          | `float` | Value substituted for variable `x`       |

**Returns** `float` — result of the expression.

**Raises**

- `ValueError` — expression is invalid or causes a math error
- `OverflowError` — result exceeds the allowed range (infinity)

**Supported syntax**

```text
Operators : + - * / ^ mod
Functions : sin cos tan asin acos atan sqrt ln log
Variable  : x
Notation  : scientific notation (1e5, 2.5e-3)
```

### `get_graph_points(expression, x_min, x_max, num_points=500)`

Compute sample points for plotting `f(x)`.

**Parameters**

| Name         | Type    | Description                                  |
|--------------|---------|----------------------------------------------|
| `expression` | `str`   | Expression containing variable `x`           |
| `x_min`      | `float` | Start of the domain                          |
| `x_max`      | `float` | End of the domain                            |
| `num_points` | `int`   | Number of sample points (default 500)        |

**Returns** `tuple[list[float], list[float | None]]` — `(xs, ys)` where `None` marks a discontinuity or out-of-range value.

**Raises** `ValueError` — if `x_min >= x_max`.

---

## LoanCalculator

```python
from model.loan import LoanCalculator
```

Computes loan payment schedules via the C shared library.

### `calculate_annuity(principal, months, annual_rate)`

Equal monthly payments throughout the term.

**Parameters**

| Name          | Type    | Description                           |
|---------------|---------|---------------------------------------|
| `principal`   | `float` | Loan amount (must be > 0)             |
| `months`      | `int`   | Term in months (must be > 0)          |
| `annual_rate` | `float` | Annual rate in percent (must be > 0)  |

**Returns** [`AnnuityResult`](#annuityresult)

**Raises** `ValueError` — if any parameter is invalid or the C library returns an error.

### `calculate_differentiated(principal, months, annual_rate)`

Decreasing payments: fixed principal portion plus diminishing interest.

**Parameters** — same as `calculate_annuity`.

**Returns** [`DifferentiatedResult`](#differentiatedresult)

**Raises** `ValueError` — if any parameter is invalid or the C library returns an error.

---

## DepositCalculator

```python
from model.deposit import DepositCalculator
```

Computes deposit growth via the C shared library.

### `calculate(amount, months, annual_rate, tax_rate, period, capitalize, additions=None, withdrawals=None)`

**Parameters**

| Name          | Type                        | Description                                           |
|---------------|-----------------------------|-------------------------------------------------------|
| `amount`      | `float`                     | Initial deposit amount (must be > 0)                  |
| `months`      | `int`                       | Term in months (must be > 0)                          |
| `annual_rate` | `float`                     | Annual interest rate in percent (must be > 0)         |
| `tax_rate`    | `float`                     | Tax on interest income in percent (0–100)             |
| `period`      | `AccrualPeriod` or `str`    | Payment periodicity — `"monthly"`, `"quarterly"`, `"annually"` |
| `capitalize`  | `bool`                      | `True` = compound interest; `False` = simple          |
| `additions`   | `list[DepositEntry] \| None` | Scheduled additions (default `None`)                 |
| `withdrawals` | `list[DepositEntry] \| None` | Scheduled withdrawals (default `None`)               |

**Returns** [`DepositResult`](#depositresult)

**Raises** `ValueError` — if any parameter is invalid or the C library returns an error.

---

## History

```python
from model.history import History
```

Persistent SQLite-backed calculation history.

**Database location**

| Platform      | Path                                |
|---------------|-------------------------------------|
| Windows       | `%APPDATA%\smartcalc_v3\history.db` |
| Linux / macOS | `~/.smartcalc_v3/history.db`        |

### `__init__(db_path=None)`

Opens (or creates) the database. Pass `db_path` to override the default location (useful in tests).

### `add_entry(expression, result)`

Append a calculation. Automatically prunes entries beyond the 1,000-entry limit.

| Parameter    | Type  | Description                    |
|--------------|-------|--------------------------------|
| `expression` | `str` | The evaluated expression       |
| `result`     | `str` | The result as a formatted string |

### `get_history()`

Returns `list[HistoryEntry]` — up to 100 most recent entries, newest first.

### `count()`

Returns `int` — total number of stored entries.

### `clear_history()`

Deletes all entries.

### `close()`

Closes the database connection. Call when the application exits.

---

## AppConfig

```python
from utils.config import AppConfig
```

Reads `src/config.ini`. All properties fall back to built-in defaults if the key is missing or invalid.

### Properties

| Property          | Type  | Default | Range / Values              |
|-------------------|-------|---------|-----------------------------|
| `theme`           | `str` | `light` | `light`, `dark`             |
| `font_size`       | `int` | `14`    | 6–72 pt                     |
| `precision`       | `int` | `7`     | 1–15 decimal digits         |
| `rotation_period` | `str` | `day`   | `hour`, `day`, `month`      |

---

## Enumerations

```python
from model.enums import PaymentType, AccrualPeriod
```

Both enums extend `StrEnum` — their values are lowercase strings usable directly in comparisons and JSON serialisation.

### PaymentType

| Member           | Value             |
|------------------|-------------------|
| `ANNUITY`        | `"annuity"`       |
| `DIFFERENTIATED` | `"differentiated"`|

### AccrualPeriod

| Member      | Value         | Periods per year |
|-------------|---------------|-----------------|
| `MONTHLY`   | `"monthly"`   | 12              |
| `QUARTERLY` | `"quarterly"` | 4               |
| `ANNUALLY`  | `"annually"`  | 1               |

---

## Result Types

```python
from model.results import (
    AnnuityResult,
    DifferentiatedResult,
    DepositResult,
    HistoryEntry,
    DepositEntry,
)
```

All types are `TypedDict` — plain dicts with typed keys, compatible with `isinstance` checks and type checkers.

### AnnuityResult

| Key               | Type    | Description                              |
|-------------------|---------|------------------------------------------|
| `monthly_payment` | `float` | Fixed monthly instalment                 |
| `overpayment`     | `float` | Total interest paid over the term        |
| `total`           | `float` | Sum of all monthly payments              |

### DifferentiatedResult

| Key             | Type          | Description                                  |
|-----------------|---------------|----------------------------------------------|
| `first_payment` | `float`       | Largest instalment (first month)             |
| `last_payment`  | `float`       | Smallest instalment (last month)             |
| `overpayment`   | `float`       | Total interest paid over the term            |
| `total`         | `float`       | Sum of all monthly payments                  |
| `payments`      | `list[float]` | Per-month amounts, chronological order       |

### DepositResult

| Key              | Type    | Description                                        |
|------------------|---------|----------------------------------------------------|
| `total_interest` | `float` | Gross interest accrued over the full term          |
| `tax_amount`     | `float` | Tax withheld on interest income                    |
| `final_amount`   | `float` | Closing balance (principal + net interest)         |

### HistoryEntry

| Key          | Type  | Description                              |
|--------------|-------|------------------------------------------|
| `expression` | `str` | Original expression entered by the user  |
| `result`     | `str` | Evaluated result as a formatted string   |
| `timestamp`  | `str` | ISO-8601 UTC datetime of the entry       |

### DepositEntry

| Key      | Type    | Description                                    |
|----------|---------|------------------------------------------------|
| `month`  | `int`   | 1-based month index within the deposit term    |
| `amount` | `float` | Amount to add or withdraw (always positive)    |
