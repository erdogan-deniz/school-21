"""Connection parameters for the day_06 spaceships exercise.

Reads from the environment with bootcamp-friendly defaults. To
override locally without leaking real credentials:

    export DB_USER=postgres
    export DB_PASSWORD=...
    export DB_NAME=spaceships
"""

import os

USER_NAME = os.environ.get("DB_USER", "postgres")
USER_PASSWORD = os.environ.get("DB_PASSWORD", "1969")
DATABASE_NAME = os.environ.get("DB_NAME", "spaceships")
