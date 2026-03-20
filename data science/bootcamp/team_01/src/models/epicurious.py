"""
A "Epicurious" module with model for website scraping.

Examples of usage:
    >>> epicurious: Epicurious = Epicurious()

    >>> epicurious.set_configuration()
    >>> urls: list = await epicurious.fetch_recipes_urls_from_website_pages([
    >>>     "Potato Chips",
    >>>     "Fish",
    >>>     "Milk",
    >>> ], )
"""


import os
import sys

sys.path.append(
    os.path.dirname(
        os.path.abspath(__file__, ),
    ),
)

from typing import Any
from bs4 import BeautifulSoup
from dotenv import load_dotenv
from httpx import (
    HTTPError,
    AsyncClient,
    ConnectTimeout,
)

from src.utils import get_clear_string


class Epicurious:
    """
    A "Epicurious" class for interacting and storing data from the web-site.

    :Attributes:
        config (dict): A configuration for working with the web-site.
                       Default: {}.
    """

    def __init__(
        self,
        config: dict[str, Any] | None = None
    ) -> None:
        """
        Initializes the "Epicurious" class representative.

        :Parameters:
            config (dict[str, Any] | None): A configuration for working with the
                                            web-site.
                                            Default: None.
        """

        self.config: dict = config or {}

    def set_configuration(self) -> None:
        """
        Sets the configuration for the class representative to work with the
        web-site.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            Exception: All other errors.
        """

        try:
            load_dotenv()

            self.config["URL"] = os.getenv("EPICURIOUS_URL", )
            self.config["BASE_URL"] = "https://www.epicurious.com"
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    async def fetch_recipe_url_from_website_page(
        self,
        req_args: str,
        async_client: AsyncClient
    ) -> str | None:
        """
        Fetch recipe URL from web-site page.

        :Parameters:
            req_args (str): An arguments for the URL request.
            async_client (AsyncClient): An asynchronous client for requests.

        :Returns:
            str: An URL from web-site page.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ConnectTimeout: When connection runtime is out.
            HTTPError: When HTTP error was raised.
            IndexError: When object do not contains expected index.
            Exception: All other errors.
        """

        try:
            req_args = get_clear_string(req_args, )
            resp: Any = await async_client.get(
                self.config["URL"],
                params={"q": req_args.replace(' ', '+', ), },
            )

            if resp.status_code == 200:
                soup: BeautifulSoup = BeautifulSoup(
                    resp.text,
                    "html.parser",
                )
                page_urls: list = soup.find_all(
                    'a',
                    string=lambda text: text and req_args in text,
                )

                if len(page_urls, ) > 0:
                    return self.config["BASE_URL"] + page_urls[0].get("href", )
        except ConnectTimeout as conn_timeout_err:
            raise ConnectTimeout(
                f"\nFile: {__file__}\n" +
                f"Message: {conn_timeout_err}.",
            )
        except HTTPError as http_err:
            raise HTTPError(
                f"\nFile: {__file__}\n" +
                f"Message: {http_err}.",
            )
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    async def fetch_recipes_urls_from_website_pages(
        self, reqs_args: list[str]
    ) -> list[str | None] | None:
        """
        Fetch recipes URL's from web-site pages.

        :Parameters:
            reqs_args (list[str]): An arguments for the URL's requests.

        :Returns:
            list[str | None]: An URL's from web-site pages.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        res_urls: list = []

        try:
            self.set_configuration()

            async with AsyncClient() as async_client:
                for req_args in reqs_args:
                    res_urls.append(
                        await self.fetch_recipe_url_from_website_page(
                            req_args,
                            async_client,
                        ),
                    )

            return res_urls
        except TypeError as type_err:
            raise TypeError(
                f"\nFile: {__file__}\n" +
                f"Message: {type_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )
