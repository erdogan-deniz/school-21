import os
import sys
import pytest

sys.path.append(os.path.join(os.path.dirname(__file__), "../ex03/"))

from financial import get_parsed_data

request_base_url: str = "https://finance.yahoo.com/quote/@TICKET@/financials/"

request_headers: dict = {
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,"
    + "image/avif,image/webp,image/png,image/svg+xml,*/*;q=0.8",
    "User-Agent": "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:131.0)"
    + " Gecko/20100101 Firefox/131.0",
}

true_parsed_data: tuple = (
    "Total Revenue",
    "245,122,000.00",
    "245,122,000.00",
    "211,915,000.00",
    "198,270,000.00",
    "168,088,000.00",
)


def test_get_parsed_data_answer(monkeypatch) -> None:
    """"""

    test_args: list = ["financial.py", "MSFT", "Total Revenue"]

    monkeypatch.setattr(sys, "argv", test_args)

    parsed_data: tuple = get_parsed_data(request_base_url, request_headers)

    assert true_parsed_data == parsed_data


def test_get_parsed_data_type(monkeypatch) -> None:
    """"""

    test_args: list = ["financial.py", "MSFT", "Total Revenue"]

    monkeypatch.setattr(sys, "argv", test_args)

    parsed_data: tuple = get_parsed_data(request_base_url, request_headers)

    assert type(parsed_data) is type(true_parsed_data)


def test_get_parsed_data_exception(monkeypatch) -> None:
    """"""

    test_args: list = ["financial.py", "XXX", "Total Revenue"]

    monkeypatch.setattr(sys, "argv", test_args)

    with pytest.raises(Exception):
        get_parsed_data(request_base_url, request_headers)
