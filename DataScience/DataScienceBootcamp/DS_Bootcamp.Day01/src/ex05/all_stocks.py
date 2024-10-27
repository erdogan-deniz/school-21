import sys


def get_dict_key_by_val(dict_: dict, val: object) -> object | None:
    """"""

    for dict_key, dict_val in dict_.items():
        if dict_val == val:
            return dict_key


def define_entity() -> None:
    """"""

    script_args: list = sys.argv

    COMPANIES: dict = {
        "Nokia": "NOK",
        "Apple": "AAPL",
        "Tesla": "TSLA",
        "Netflix": "NFLX",
        "Microsoft": "MSFT",
    }

    STOCKS: dict = {
        "NOK": 3.37,
        "AAPL": 287.73,
        "MSFT": 173.79,
        "NFLX": 416.90,
        "TSLA": 724.88,
    }

    if (len(script_args) == 2) and isinstance(script_args[1], str):
        if ",," in script_args[1].replace(" ", ""):
            return None

        entities: list = script_args[1].replace(" ", "").split(",")

        for entity in entities:
            if entity.upper() in COMPANIES.values():
                print(
                    f"{entity} is a ticker symbol for {
                        get_dict_key_by_val(COMPANIES, entity)}"
                )
            elif entity.capitalize() in COMPANIES.keys():
                company_ticket: str = COMPANIES[entity.capitalize()]

                print(
                    f"{entity.capitalize()} stock price is {
                        STOCKS[company_ticket]}"
                )
            else:
                print(
                    entity, "is an unknown company or an unknown ticker symbol"
                )


if __name__ == "__main__":
    define_entity()
