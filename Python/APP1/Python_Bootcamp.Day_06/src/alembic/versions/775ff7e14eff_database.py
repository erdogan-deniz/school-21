"""database

Revision ID: 775ff7e14eff
Revises:
Create Date: 2024-01-25 05:42:48.194181

"""
from typing import Sequence, Union

from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision: str = '775ff7e14eff'
down_revision: Union[str, None] = None
branch_labels: Union[str, Sequence[str], None] = None
depends_on: Union[str, Sequence[str], None] = None


def upgrade() -> None:
    op.create_table(
        "spaceships",
        sa.Column('id', sa.Integer, primary_key=True),
        sa.Column('alignment', sa.String(), nullable=False),
        sa.Column('name', sa.String(), nullable=False),
        sa.Column('type', sa.String(), nullable=False),
        sa.Column('length', sa.Float(), nullable=False),
        sa.Column('crew_size', sa.Integer(), nullable=False),
        sa.Column('armed', sa.String(), nullable=False)
    )

    op.create_table(
        "officers",
        sa.Column('id', sa.Integer, primary_key=True),
        sa.Column('first_name', sa.String(), nullable=False),
        sa.Column('last_name', sa.String(), nullable=False),
        sa.Column('rank', sa.String(), nullable=False)
    )

    op.create_table(
        "traitors",
        sa.Column('id', sa.Integer, primary_key=True),
        sa.Column('first_name', sa.String(), nullable=False),
        sa.Column('last_name', sa.String(), nullable=False),
        sa.Column('rank', sa.String(), nullable=False)
    )


def downgrade() -> None:
    op.drop_table("spaceships")
    op.drop_table("officers")
    op.drop_table("traitors")
