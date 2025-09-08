"""
Exercise 06: a movies - solution module.
"""


from json import (
    JSONDecodeError,
    load,
    dumps,
)


def main(file: str, file_path: str) -> None:
    """
    Exercise 06 solution function.

    :Parameters:
        file (str): A ".json" file with movies data.
        file_path (str): A path to the ".json" file.

    :Exceptions:
        FileNotFoundError: When tried to use a non-existent file.
        JSONDecodeError: When json parser can not decode data.
        TypeError: When used incorrect data types.
        KeyError: When used incorrect key.
        Exception: All other errors.
    """

    try:
        movies_lists: dict = {}

        with open(
            encoding="utf-8",
            file=file_path + file,
        ) as file:
            movies_lists = load(file, )

        movies_list: list[dict[str, int]] = movies_lists["list_one"] +\
                                            movies_lists["list_two"]

        movies_list.sort(key=lambda movie: movie["year"], )
        print(dumps(
            {"list": movies_list, },
            indent=4,
            ensure_ascii=False,
        ), )
    except FileNotFoundError as file_not_found_err:
        raise FileNotFoundError(
            f"\nFile: {__file__}\n" +
            f"Message: {file_not_found_err}.",
        )
    except JSONDecodeError as json_dec_err:
        raise JSONDecodeError(
            f"\nFile: {__file__}\n" +
            f"Message: {json_dec_err}.",
        )
    except TypeError as type_err:
        raise TypeError(
            f"\nFile: {__file__}\n" +
            f"Message: {type_err}.",
        )
    except KeyError as key_err:
        raise KeyError(
            f"\nFile: {__file__}\n" +
            f"Message: {key_err}.",
        )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main("movies.json", "data/json/", )
