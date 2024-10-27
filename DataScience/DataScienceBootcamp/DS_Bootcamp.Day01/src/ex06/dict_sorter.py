def get_dict_keys_by_val(dict_: dict, val: object) -> list:
    """"""

    dict_keys: list = []

    for dict_key, dict_val in dict_.items():
        if dict_val == val:
            dict_keys.append(dict_key)

    dict_keys.sort()

    return dict_keys


def list_to_sorted_dict() -> None:
    """"""

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

    dict_of_tuples: dict = {pair[0]: pair[1] for pair in list_of_tuples}

    vals: list = list(set(dict_of_tuples.values()))

    vals.sort(key=int, reverse=True)

    for val in vals:
        res = get_dict_keys_by_val(dict_of_tuples, val)

        print(*res, sep="\n")


if __name__ == "__main__":
    list_to_sorted_dict()
