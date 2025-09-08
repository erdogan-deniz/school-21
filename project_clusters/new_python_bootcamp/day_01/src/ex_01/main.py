"""
Exercise 01: a scalar product - solution module.
"""


from models.vector import Vector


def main() -> None:
    """
    Exercise 01 solution function.

    :Exceptions:
        Exception: All other errors.
    """

    try:
        vec_one: Vector = Vector()
        vec_two: Vector = Vector()

        vec_one.input_vector_coordinates()
        vec_two.input_vector_coordinates()
        print(
            f"\n{Vector.calculate_vectors_scalar_product(vec_one, vec_two, )}",
        )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main()
