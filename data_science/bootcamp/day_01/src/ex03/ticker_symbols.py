import sys


def get_dict_key_by_val(dict_: dict, val: object) -> object | None:
    """"""

    for dict_key, dict_val in dict_.items():
        if dict_val == val:
            return dict_key


def get_company_stock_price() -> None:
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

    if len(script_args) == 2:
        if script_args[1].upper() in COMPANIES.values():
            company_name: str = get_dict_key_by_val(
                COMPANIES, script_args[1].upper()
            )
            company_ticket: str = script_args[1].upper()

            print(company_name, STOCKS[company_ticket])
        else:
            print("Unknown company")


if __name__ == "__main__":
    get_company_stock_price()
