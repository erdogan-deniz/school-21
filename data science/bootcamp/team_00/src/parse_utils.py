"""
Module of web parse utils.

Examples of usage:
    >>> print(fetch_webpage_text(
    >>>     url="https://www.imdb.com/title/tt0113041",
    >>>     headers={
    >>>         "Accept-Language": "ru,en;q=0.9,de;q=0.8",
    >>>         "Accept-Encoding": "gzip, deflate, br, zstd",
    >>>         "Accept": "text/html,application/xhtml+xml,application/xml;" +
    >>>                   "q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8," +
    >>>                   "application/signed-exchange;v=b3;q=0.7",
    >>>         "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) " +
    >>>                       "AppleWebKit/537.36 (KHTML, like Gecko) Chrome" +
    >>>                       "/134.0.0.0 YaBrowser/25.4.0.0 Safari/537.36",
    >>>     },
    >>> ), )

    >>> print(fetch_movie_webpage_text_fields(
    >>>     movie_id="0113041",
    >>>     movie_webpage_text=fetch_webpage_text(
    >>>         url="https://www.imdb.com/title/tt0113041",
    >>>         headers={
    >>>             "Accept-Language": "ru,en;q=0.9,de;q=0.8",
    >>>             "Accept-Encoding": "gzip, deflate, br, zstd",
    >>>             "Accept": "text/html,application/xhtml+xml,application/" +
    >>>                        "xml;q=0.9,image/avif,image/webp,image/apng,*/" +
    >>>                        "*;q=0.8,application/signed-exchange;v=b3;q=0.7",
    >>>             "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) " +
    >>>                           "AppleWebKit/537.36 (KHTML, like Gecko) " +
    >>>                           "Chrome/134.0.0.0 YaBrowser/25.4.0.0 Safari" +
    >>>                           "/537.36",
    >>>         },
    >>>     ),
    >>> ), )

    >>> print(fetch_movie_webpage_text_field(
    >>>     soup=BeautifulSoup(
    >>>         fetch_webpage_text(
    >>>             url="https://www.imdb.com/title/tt0113041",
    >>>             headers={
    >>>                 "Accept-Language": "ru,en;q=0.9,de;q=0.8",
    >>>                 "Accept-Encoding": "gzip, deflate, br, zstd",
    >>>                 "Accept": "text/html,application/xhtml+xml,applicat" +
    >>>                           "ion/xml;q=0.9,image/avif,image/webp,image/" +
    >>>                           "apng,*/*;q=0.8,application/signed-exchange" +
    >>>                           ";v=b3;q=0.7",
    >>>                 "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; " +
    >>>                               "x64) AppleWebKit/537.36 (KHTML, like " +
    >>>                               "Gecko) Chrome/134.0.0.0 YaBrowser/25.4" +
    >>>                               ".0.0 Safari/537.36",
    >>>             },
    >>>         ),
    >>>         "html.parser",
    >>>     ),
    >>>     field="title",
    >>> ), )

    >>> print(fetch_movies_webpage_text_fields(movies_ids=[
    >>>     "0112302",
    >>>     "0113497",
    >>>     "0114709",
    >>>     "0113501",
    >>>     "0113627",
    >>> ], ), )
"""


from typing import Literal
from bs4 import BeautifulSoup
from requests import Response, get
from json import JSONDecodeError, load
from bs4.builder import ParserRejectedMarkup
from requests.exceptions import (
    Timeout,
    HTTPError,
    RequestException,
)


def fetch_webpage_text(url: str, headers: dict[str, str]) -> str | None:
    """
    Fetch and return the text of a webpage.

    :Parameters:
        url (str): The URL to fetch.
        headers (dict[str, str]): HTTP headers.

    :Returns:
        str: Webpage text.
        None: If error occurs or no data is loaded.

    :Exceptions:
        Timeout: When requests timeout has been reached.
        HTTPError: When raised a HTTP error.
        RequestException: When request has error.
        Exception: All other errors.
    """

    try:
        res: Response = get(
            url=url,
            headers=headers,
            timeout=10,
        )

        return res.text if res.status_code == 200 else None
    except Timeout as timeout_err:
        print("Timeout:", timeout_err, )
    except HTTPError as http_err:
        print("HTTPError:", http_err, )
    except RequestException as req_err:
        print("RequestException:", req_err, )
    except Exception as err:
        print("Exception:", err, )

def fetch_movie_webpage_text_fields(
    movie_id: str,
    movie_webpage_text: str,
    fields: Literal[
        "gross",
        "title",
        "budget",
        "rating",
        "writer",
        "runtime",
        "release",
        "country",
        "director",
        "language",
    ] = [
        "gross",
        "title",
        "budget",
        "rating",
        "writer",
        "runtime",
        "release",
        "country",
        "director",
        "language",
    ]
) -> list[str] | None:
    """
    Fetch movie fields from webpage text.

    :Parameters:
        movie_id (str): Movie ID.
        movie_webpage_text (str): Movie webpage text.
        fields (Literal["gross", "title", "budget", "rating", "writer",
                        "runtime", "release", "country", "director", language",
        ]): Fields names to extract.
            Default: ["gross", "title", "budget", "rating", "writer", "runtime",
                      "release", "country", "director", language", ].

    :Returns:
        list[str]: List with fields values.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        ValueError: When used invalid data format.
        ParserRejectedMarkup: When can not parse webpage.
        Exception: All other errors.
    """

    try:
        fields_vals: list[str] = [movie_id, ]
        soup: BeautifulSoup = BeautifulSoup(movie_webpage_text, "html.parser", )

        for field in fields:
            fields_vals.append(fetch_movie_webpage_text_field(
                field=field,
                soup=soup,
            ), )

        return fields_vals
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except ParserRejectedMarkup  as parser_rej_markup_err:
        print("ParserRejectedMarkup:", parser_rej_markup_err, )
    except Exception as err:
        print("Exception:", err, )

def fetch_movie_webpage_text_field(
    soup: BeautifulSoup,
    field: str
) -> str | None:
    """
    Fetch movie field.

    :Parameters:
        soup (BeautifulSoup): Parsed webpage.
        field (str): Field name.

    :Returns:
        str: Movie webapge field value.
        None: If error occurs or no data is loaded.

    :Exceptions:
        TypeError: When used incorrect data types.
        ValueError: When used invalid data format.
        Exception: All other errors.
    """

    try:
        match field.lower():
            case "gross":
                return soup.find(
                    "section",
                    attrs={"data-testid": "BoxOffice", },
                ).find(
                    "li",
                    attrs={
                        "data-testid":
                            "title-boxoffice-cumulativeworldwidegross",
                    },
                ).find(
                    "span",
                    class_="ipc-metadata-list-item__list-content-item ipc-btn" +
                           "--not-interactable",
                ).get_text(strip=True, )

            case "title":
                return soup.find(
                    "h1",
                    attrs={"data-testid": "hero__pageTitle", },
                ).find("span", ).get_text()

            case "budget":
                return soup.find(
                    "section",
                    attrs={"data-testid": "BoxOffice", },
                ).find(
                    "li",
                    attrs={"data-testid": "title-boxoffice-budget", },
                ).find(
                    "span",
                    class_="ipc-metadata-list-item__list-content-item ipc-btn" +
                           "--not-interactable",
                ).get_text(strip=True, ).split()[0]

            case "rating":
                return soup.find(
                    "div",
                    attrs={
                        "data-testid":
                            "hero-rating-bar__aggregate-rating__score",
                    },
                ).find("span", ).get_text()

            case "runtime":
                return soup.find(
                    "section",
                    attrs={"data-testid": "TechSpecs", },
                ).find(
                    "li",
                    attrs={"data-testid": "title-techspec_runtime", },
                ).find("div", ).get_text()

            case "writer":
                return soup.find(
                    "div",
                    class_="ipc-metadata-list-item__content-container",
                ).get_text()

            case "release":
                return soup.find(
                    "section",
                    attrs={"data-testid": "Details", },
                ).find(
                    "li",
                    attrs={"data-testid": "title-details-releasedate", },
                ).get_text().split('(', )[0].split("Release date", )[1]

            case "country":
                return soup.find(
                    "section",
                    attrs={"data-testid": "Details", },
                ).find(
                    "li",
                    attrs={"data-testid": "title-details-origin", },
                ).find('a', ).get_text()

            case "director":
                return soup.find(
                    'a',
                    class_="ipc-metadata-list-item__list-content-item",
                ).get_text(strip=True, )

            case "language":
                return soup.find(
                    "section",
                    attrs={"data-testid": "Details", },
                ).find(
                    "li",
                    attrs={"data-testid": "title-details-languages", },
                ).find('a', ).get_text().lower()
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except Exception as err:
        print("Exception:", err, )

def fetch_movies_webpage_text_fields(
    movies_ids : list[str],
    fields: list[Literal[
        "gross", "title", "budget", "rating", "writer", "runtime", "release",
        "country", "director", "language",
    ]] = [
        "gross",
        "title",
        "budget",
        "rating",
        "writer",
        "runtime",
        "release",
        "country",
        "director",
        "language",
    ],
    req_config_path: str = "data/",
    req_config_file: str = "request.json"
) -> list[list[str]] | None:
    """
    Fetch movies webpage fields.

    :Parameters:
        movies_ids (list[str]): Movies IDs.
        fields (list[Literal["gross", "title", "budget", "rating", "writer",
                             "runtime", "release", "country", "director",
                             "language",
        ]]): Movies webpage fields to extract.
             Default: ["gross", "title","budget", "rating", "writer", "runtime",
                       "release", "country", "director", "language",
                       ].
        req_config_path (str): A path to requests configuration file.
                               Default: "data/".
        req_config_file (str): A requests configuration file.
                               Default: "request.json"

        :Returns:
            list[list[str]]: Movies webpage fields values.
            None: If error occurs or no data is loaded.

        :Exceptions:
            FileNotFoundError: When file does not exist.
            JSONDecodeError: When used incorrect JSON value.
            ValueError: When used incorrect data types.
            Exception: All other errors.
        """

    try:
        with open(
            file=req_config_path + req_config_file,
            mode='r',
            encoding="utf-8",
        ) as file:
            req_config: dict[str, str] = load(file, )

        movies_data: list[list[str]] = []

        for movie_id in movies_ids:
            movies_data.append(fetch_movie_webpage_text_fields(
                movie_id=movie_id,
                movie_webpage_text=fetch_webpage_text(
                    url=req_config["imdb_url"] + movie_id,
                    headers=req_config["headers"],
                ),
                fields=fields,
            ), )

        return sorted(
            movies_data,
            key=lambda movie_data: movie_data[0],
            reverse=True,
        )
    except FileNotFoundError as file_not_found_err:
        print("FileNotFoundError:", file_not_found_err, )
    except JSONDecodeError as json_dec_err:
        print("JSONDecodeError:", json_dec_err, )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except Exception as err:
        print("Exception:", err, )
