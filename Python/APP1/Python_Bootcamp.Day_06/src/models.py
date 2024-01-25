from sqlalchemy.orm import Mapped, mapped_column, DeclarativeBase


# Base class for all entity:
class Base(DeclarativeBase):
    id: Mapped[int] = mapped_column(primary_key=True, autoincrement=True)


# Spaceship class:
class Spaceship(Base):
    __tablename__ = "spaceships"

    alignment: Mapped[str]
    name: Mapped[str]
    type: Mapped[str]
    length: Mapped[float]
    crew_size: Mapped[int]
    armed: Mapped[str]


# Class for officers:
class Officer(Base):
    __tablename__ = 'officers'

    first_name: Mapped[str]
    last_name: Mapped[str]
    rank: Mapped[str]
    spaceship_id: Mapped[int]
    status: Mapped[str]


# Class of traitors:
class Traitors(Base):
    __tablename__ = 'traitors'

    first_name: Mapped[str]
    last_name: Mapped[str]
    rank: Mapped[str]
