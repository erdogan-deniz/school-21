# `sql/bootcamp`

[![CI](https://github.com/erdogan-deniz/school-21/actions/workflows/sql.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/sql.yml)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](../../LICENSE)

> *Day-by-day School 21 SQL Bootcamp — relational model → JOINs → relational algebra → DML → views → indexes → schema design → OLAP → transaction isolation → procedures, plus 2 team projects (TSP-in-SQL and a full DWH/ETL).*

## Quick start

```bash
cd sql/bootcamp

make up                 # spin up Postgres 16 in Docker (blocks until healthy)
make seed DAY=00        # load day_00/materials/model.sql into the bootcamp db
make psql DAY=00        # seed + drop into an interactive psql shell
make test-all           # smoke-test every day's schema in a fresh public schema
make down               # tear down (drops the volume)
```

That gets you a clean Postgres 16 on `localhost:5432`
(`user=school21 / pass=school21 / db=bootcamp`) with the chosen day's
schema preloaded. The entire bootcamp tree is bind-mounted at
`/workspace` inside the container, so `\i /workspace/day_NN/src/...` works
from the psql shell without extra setup.

Per-day exercises live under `day_NN/src/`; run individual scripts as
`make psql DAY=NN` then `\i src/<script>.sql`.

For lint:

```bash
pip install sqlfluff==3.2.5
sqlfluff lint sql/ --dialect postgres
```

CI runs the same lint and `make test-all` equivalents — see
[`.github/workflows/sql.yml`](../../.github/workflows/sql.yml).

## Demo

> **TODO** — short asciinema cast of an OLAP day (Day 07) or a transaction-isolation walkthrough (Day 08) is planned in the sql/ Phase 2 demo slice.

## Documentation

- Per-day `README.md` files under `day_00/` … `day_09/`, `team_00/`, `team_01/`.
- Day-by-day index below.

## Tests

- Lint via **sqlfluff** in [`.github/workflows/sql.yml`](../../.github/workflows/sql.yml).
- Per-day end-to-end runs against a Postgres service container: TBD as days
  are reviewed individually.

## License & attribution

This project was developed as part of the **School 21** curriculum (analogue of
School 42). The repository as a whole is licensed under the **MIT License** —
see the root [`LICENSE`](../../LICENSE).

The per-day `LICENSE` files (`# School 21 License`) under `day_*/` are
preserved as educational attribution and historical artefact; they do not
override the repo-wide MIT licence.

---

## Original task (School 21)

Project topic: SQL Bootcamp.

### Day 00: Working with a relational database and SQL statements

— Used SELECT queries with: filtering, sorting, string concatenation, aliases, subqueries, conditional logic, and functions.

### Day 01: Working with sets and JOINs

— Utilized set operations.
— Used JOINs: CROSS JOIN, INNER JOIN, NATURAL JOIN.

### Day 02: Working with relational algebra

— Applied CTEs in practice.
— Aggregated data using functions.

### Day 03: Using SQL DML statements

— Inserted data into the database using the INSERT statement.
— Modified data in the database using the UPDATE statement.
— Deleted data from the database using the DELETE statement.

### Day 04: Working with views and time ranges

— Created views with date sequence generation.
— Created materialized views.
— Dropped views after use.

### Day 05: Creating and applying indexes

— Created indexes and composite indexes based on B-trees.
— Analyzed queries using EXPLAIN ANALYZE.

### Day 06: Integrating business ideas into the data model

— Created tables with primary and foreign keys.
— Set data constraints.

### Day 07: Using OLAP constructions to gain insights from data

— Performed multiple aggregations and data groupings.

### Day 08: Exploring transaction isolation levels

— Investigated anomalies and mechanisms: "Dirty Read", "Lost Update", "Non-Repeatable Read", "Phantom Read".
— Studied isolation levels: READ COMMITTED, REPEATABLE READ, SERIALIZABLE.
— Analyzed deadlocks.

### Day 09: Storing procedures in the database

— Created a trigger with a TG_OP condition for operation logging.
— Created a function with a loop to generate a Fibonacci sequence.

### Team 00: Solving the traveling salesman problem using SQL

### Team 01: Creating a DWH and developing an ETL pipeline

— Developed a DWH.
— Calculated statistical characteristics of data using aggregation.
— Created an ETL pipeline.
