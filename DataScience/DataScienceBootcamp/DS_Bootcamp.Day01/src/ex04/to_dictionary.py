def list_to_dict() -> None:
    """"""

    dict_: dict = {}

    list_of_tuples: list = [
        ("Iran", "76"),
        ("China", "83"),
        ("Israel", "12"),
        ("Russia", "25"),
        ("Spain", "178"),
        ("Italy", "162"),
        ("Finland", "3"),
        ("Hungary", "2"),
        ("Turkey", "65"),
        ("Canada", "28"),
        ("Brazil", "25"),
        ("France", "132"),
        ("Belgium", "34"),
        ("Austria", "14"),
        ("Germany", "132"),
        ("Portugal", "17"),
        ("The USA", "610"),
        ("Switzerland", "26"),
        ("The Netherlands", "28"),
        ("The United Kingdom", "95"),
    ]

    [dict_.setdefault(pair[1], []).append(pair[0]) for pair in list_of_tuples]

    [print(f"'{key}' : '{val}'") for key in dict_ for val in dict_[key]]


if __name__ == "__main__":
    list_to_dict()
