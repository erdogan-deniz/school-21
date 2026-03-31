"""Abstract base class for models with a rectangular field."""

from abc import ABC, abstractmethod

from utils.config import MAX_COLS, MAX_ROWS


class BaseField(ABC):
    """Abstract base class for models with a rectangular field."""

    rows: int
    cols: int

    def __init__(
        self,
        rows: int,
        cols: int,
        max_rows: int = MAX_ROWS,
        max_cols: int = MAX_COLS,
    ) -> None:
        """
        Args:
            rows: number of rows
            cols: number of columns
            max_rows: maximum number of rows
            max_cols: maximum number of columns
        """

        self._check_sizes(rows, cols, max_rows, max_cols)

        self.rows = rows
        self.cols = cols

    def _check_sizes(
        self,
        rows: int,
        cols: int,
        max_rows: int = MAX_ROWS,
        max_cols: int = MAX_COLS,
    ) -> None:
        """Checks that rows and cols are within the allowed ranges.

        Args:
            rows: number of rows to validate
            cols: number of columns to validate
            max_rows: maximum allowed number of rows
            max_cols: maximum allowed number of columns

        Raises:
            ValueError: if rows or cols are outside the allowed range.
        """
        if not self._check_dim(rows, max_rows):  # pragma: no cover
            raise ValueError(f"Invalid rows number {rows}.")
        if not self._check_dim(cols, max_cols):  # pragma: no cover
            raise ValueError(f"Invalid columns number {cols}.")

    def _check_dim(self, size: int, max_size: int) -> bool:
        """Checks that a single field dimension is valid
        (0 <= size <= max_size).

        Args:
            size: dimension value to validate
            max_size: maximum allowed value

        Returns:
            True if the value is valid.

        Raises:
            ValueError: if the value is negative or exceeds max_size.
        """
        if size > max_size:
            raise ValueError(f"Max field size is - {max_size}")
        if size < 0:
            raise ValueError("The field dimensions cannot be negative.")
        return True

    def get_rows(self) -> int:
        """Returns the current number of rows in the field."""
        return self.rows

    def get_cols(self) -> int:
        """Returns the current number of columns in the field."""
        return self.cols

    def _init_field(self, field_mtx: list[list[int]] | None) -> list[list[int]]:
        """Initializes the field matrix: creates an empty one when None,
        or validates and copies the provided one.

        Args:
            field_mtx: a ready matrix of values (0/1) or None
                to create an empty matrix.

        Returns:
            A deep copy of the provided matrix, or a matrix filled with None.

        Raises:
            ValueError: if the matrix dimensions do not match rows/cols
                or contain invalid values.
        """
        if field_mtx is None:
            return []

        if len(field_mtx) != self.rows:
            raise ValueError(
                f"The matrix must have {self.rows} rows, "
                f"{len(field_mtx)} were received"
            )

        for i, row in enumerate(field_mtx):
            if len(row) != self.cols:
                raise ValueError(
                    f"Row [{i}] in the matrix "
                    f"must have {self.cols} columns, "
                    f"{len(row)} were received"
                )
            for j, val in enumerate(row):
                if val not in (0, 1):
                    raise ValueError(
                        f"Matrix [{i}][{j}] contains "
                        f"an invalid value: {val}. "
                        f"Only 0 and 1 are allowed."
                    )

        return [row[:] for row in field_mtx]

    def __repr__(self) -> str:  # pragma: no cover
        """Returns a string of the form ClassName(rows=N, cols=M)
        for debugging."""
        return f"{self.__class__.__name__}(rows={self.rows}, cols={self.cols})"

    def __str__(self) -> str:  # pragma: no cover
        """Returns a text representation of the field via visualize()."""
        return self.visualize()

    @abstractmethod
    def visualize(self) -> str:  # pragma: no cover
        """Returns a text representation of the model."""
        pass
