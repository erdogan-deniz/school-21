"""add new column

Revision ID: ea99e7e19ecd
Revises: 775ff7e14eff
Create Date: 2024-01-25 06:05:09.459325

"""
import sqlalchemy as sa

from alembic import op
from typing import Sequence, Union


# revision identifiers, used by Alembic.
revision: str = 'ea99e7e19ecd'
down_revision: Union[str, None] = '775ff7e14eff'
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    new_column = Column("speed", Integer())
    spaceships.append_column(new_column)


def downgrade() -> None:
    pass
