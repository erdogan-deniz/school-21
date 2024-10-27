def data_types() -> None:
    """"""

    int_var: int = 1991
    list_var: list = []
    bool_var: bool = True
    float_var: float = 3.14
    dict_var: dict = {1: 2}
    set_var: set = {1, 2, 3}
    tuple_var: tuple = (1, 2, 3)
    str_var: str = "Hello, world!"

    vars_types: list = [
        type(int_var).__name__,
        type(str_var).__name__,
        type(float_var).__name__,
        type(bool_var).__name__,
        type(list_var).__name__,
        type(dict_var).__name__,
        type(tuple_var).__name__,
        type(set_var).__name__,
    ]

    data_types_raw: str = str(vars_types)

    [print(data_types_raw.replace("'", ""))]


if __name__ == "__main__":
    data_types()
