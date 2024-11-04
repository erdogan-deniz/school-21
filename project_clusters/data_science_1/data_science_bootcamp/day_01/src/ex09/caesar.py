import sys


def get_encoded_string(initial_string: str, shift_val: int) -> str | None:
    """"""

    encoded_string: str = ""

    for symbol in initial_string:
        if "a" <= symbol <= "z":
            encoded_string += chr(96 + (ord(symbol) - 96 + shift_val) % 26)
        elif (ord(symbol) > 127) or (ord(symbol) < 32):
            raise ValueError("ERROR! Incorrect character.")
        else:
            encoded_string += symbol

    return encoded_string


def get_decoded_string(initial_string: str, shift_val: int) -> str | None:
    """"""

    decoded_string: str = ""

    for symbol in initial_string:
        if "a" <= symbol <= "z":
            decoded_string += chr(96 + (ord(symbol) - 96 - shift_val) % 26)
        elif (ord(symbol) > 127) or (ord(symbol) < 32):
            raise ValueError("ERROR! Incorrect character.")
        else:
            decoded_string += symbol

    return decoded_string


def get_processed_string() -> str | None:
    """"""

    script_args: list = sys.argv

    if len(script_args) == 4:
        processed_string: str = None
        shift_val: int = int(script_args[3])
        initial_string: str = script_args[2]

        if script_args[1] == "decode":
            processed_string = get_decoded_string(initial_string, shift_val)
        elif script_args[1] == "encode":
            processed_string = get_encoded_string(initial_string, shift_val)

        return processed_string
    else:
        raise Exception("ERROR! Incorrect arguments.")


if __name__ == "__main__":
    print(get_processed_string())
