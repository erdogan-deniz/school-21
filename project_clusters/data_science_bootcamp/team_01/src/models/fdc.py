"""
A "Food Data Central" module with model for working with API.

Examples of usage:
    >>> fdc: FDC = FDC()

    >>> fdc.set_configuration()
"""


import os
import sys

sys.path.append(
    os.path.dirname(
        os.path.abspath(__file__, ),
    ),
)

from typing import Any
from pandas import DataFrame
from dotenv import load_dotenv
from json import JSONDecodeError, load
from httpx import (
    HTTPError,
    AsyncClient,
    AsyncClient,
    ConnectTimeout,
)

from src.utils import get_conversion_multiplier_to_g


class FDC:
    """
    A "Food Data Central" class for interacting and storing data from the API.

    :Attributes:
        config (dict): A configuration for working with the API.
                       Default: {}.
    """

    def __init__(
        self,
        config: dict[str, Any] | None = None
    ) -> None:
        """
        Initializes the "Food Data Central" class representative.

        :Parameters:
            config (dict[str, Any] | None): A configuration for working with the
                                            API.
                                            Default: None.
        """

        self.config: dict = config or {}

    @staticmethod
    def parse_ingredient_nutrients_data(
        ingredient_data: dict[str, Any]
    ) -> list[list[str | None, float, str]] | None:
        """
        Extracts a nutrients data from ingredient data.

        :Parameters:
            ingredient_data (dict[str, Any]): An ingredient data.

        :Returns:
            list[list[str | None, float, str]]: An parsed ingredient nutrients
                                                data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            IndexError: When object do not contains expected index.
            KeyError: When object does not has a key.
            Exception: All other errors.
        """

        ingredient_nutrients_data: list = []

        try:
            nutrients_data: list[dict[str, Any]] = ingredient_data.get(
                "foods",
                None,
            )[0].get(
                "foodNutrients",
                None,
            )

            for nutrient_data in nutrients_data:
                ingredient_nutrients_data.append([
                    nutrient_data.get(
                        "nutrientName",
                        None,
                    ),
                    nutrient_data.get(
                        "value",
                        0,
                    ),
                    nutrient_data.get(
                        "unitName",
                        'g',
                    ),
                ], )

            return ingredient_nutrients_data
        except IndexError as idx_err:
            raise IndexError(
                f"\nFile: {__file__}\n" +
                f"Message: {idx_err}.",
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

    @staticmethod
    def parse_ingredients_nutrients_data(
        ingredients_data: list[dict[str, Any]]
    ) -> list[list[list[str | None, float, str]]] | None:
        """
        Extracts a nutrients data from ingredients data.

        :Parameters:
            ingredients_data (list[dict[str, Any]]): An ingredients data.

        :Returns:
            list[list[list[str | None, float, str]]]: An parsed ingredients
                                                      nutrients data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        ingredients_nutrients_data: list = []

        try:
            for ingredient_data in ingredients_data:
                ingredients_nutrients_data.append(
                    FDC.parse_ingredient_nutrients_data(ingredient_data, ),
                )

            return ingredients_nutrients_data
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    @staticmethod
    def standardize_ingredient_nutrient_data(
        ingredient_nutrient_data: list[str | None, float, str]
    ) -> list[str, float] | None:
        """
        Standardize an ingredient nutrient data.

        :Parameters:
            ingredient_nutrient_data (list[str | None, float, str]):
            An ingredient nutrient data.

        :Returns:
            list[str, float]: An standardized ingredient nutrient data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            Exception: All other errors.
        """

        try:
            nutrient_name: str | None = ingredient_nutrient_data[0]
            nutrient_num: float = ingredient_nutrient_data[1]
            nutrient_unit: str = ingredient_nutrient_data[2]

            match nutrient_name.lower():
                case "protein":
                    return [
                        "protein",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "total lipid (fat)":
                    return [
                        "fat",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "carbohydrate, by difference":
                    return [
                        "carbohydrate",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "total sugars":
                    return [
                        "sugars",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "fiber, total dietary":
                    return [
                        "fiber",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "calcium, ca":
                    return [
                        "calcium",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "iron, fe":
                    return [
                        "iron",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "sodium, na":
                    return [
                        "sodium",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin a, iu" | "vitamin a, rae":
                    return [
                        "vitamin a",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin c, total ascorbic acid":
                    return [
                        "vitamin c",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "cholesterol":
                    return [
                        "cholesterol",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "fatty acids, total saturated":
                    return [
                        "saturated fat",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "potassium, k":
                    return [
                        "potassium",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin d (d2 + d3), international units" |\
                    "vitamin d (d2 + d3)":
                    return [
                        "vitamin d",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "magnesium, mg":
                    return [
                        "magnesium",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "phosphorus, p":
                    return [
                        "phosphorus",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "zinc, zn":
                    return [
                        "zinc",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "copper, cu":
                    return [
                        "copper",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "selenium, se":
                    return [
                        "selenium",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin e (alpha-tocopherol)":
                    return [
                        "vitamin e",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "thiamin":
                    return [
                        "thiamin",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "riboflavin":
                    return [
                        "riboflavin",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "niacin":
                    return [
                        "niacin",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin b-6":
                    return [
                        "vitamin b 6",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "folate, total":
                    return [
                        "folate",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin b-12":
                    return [
                        "vitamin b 12",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "choline, total":
                    return [
                        "choline",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "vitamin k (phylloquinone)":
                    return [
                        "vitamin k",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "manganese, mn":
                    return [
                        "manganese",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "pantothenic acid":
                    return [
                        "pantothenic acid",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
                case "biotin":
                    return [
                        "biotin",
                        nutrient_num * get_conversion_multiplier_to_g(
                            nutrient_unit,
                        ),
                    ]
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

    @staticmethod
    def standardize_ingredient_nutrients_data(
        ingredient_nutrients_data: list[list[str | None, float, str]]
    ) -> list[list[str, float]] | None:
        """
        Standardize an ingredient nutrients data.

        :Parameters:
            ingredient_nutrients_data (list[list[str | None, float, str]]):
            An ingredient nutrients data.

        :Returns:
            list[list[str, float]]: An standardized ingredient nutrients data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            std_ingredient_nutrients_data: list = []

            for ingredient_nutrient_data in ingredient_nutrients_data:
                loc_ingredient_nutrient_data: list[
                    str, float
                ] | None = FDC.standardize_ingredient_nutrient_data(
                    ingredient_nutrient_data,
                )

                if loc_ingredient_nutrient_data is not None:
                    std_ingredient_nutrients_data.append(
                        loc_ingredient_nutrient_data,
                    )

            return std_ingredient_nutrients_data
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

    @staticmethod
    def standardize_ingredients_nutrients_data(
        ingredients_nutrients_data: list[list[list[str | None, float, str]]]
    ) -> list[list[list[str, float]]] | None:
        """
        Standardize an ingredients nutrients data.

        :Parameters:
            ingredients_nutrients_data (
                list[list[list[str | None, float, str]]]
            ): An ingredients nutrients data.

        :Returns:
            list[list[list[str, float]]]: An standardized ingredients nutrients
                                          data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        try:
            std_ingredients_nutrients_data: list = []

            for ingredient_nutrients_data in ingredients_nutrients_data:
                std_ingredients_nutrients_data.append(
                    FDC.standardize_ingredient_nutrients_data(
                        ingredient_nutrients_data,
                    ),
                )

            return std_ingredients_nutrients_data
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

    @staticmethod
    def get_standardized_ingredient_nutrients_data(
        necess_nutrients: list[str],
        std_ingredient_nutrients_data: list[list[str, float]]
    ) -> dict[str, float] | None:
        """
        Returns an ingredient nutrients standardized data.

        :Parameters:
            necess_nutrients (list[str]): A names of the necessary nutrients.
            std_ingredient_nutrients_data (list[list[str, float]]):
                An standardized ingredient nutrients data.

        :Returns:
            dict[str, float]: An standardized ingredient nutrients data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            KeyError: When objec does not has a key.
            Exception: All other errors.
        """

        try:
            nutrients: dict[str, float] = {
                nutrient: 0
                for nutrient
                in necess_nutrients
            }

            for std_ingredient_nutrient_data in std_ingredient_nutrients_data:
                nutrients[std_ingredient_nutrient_data[0]] =\
                    std_ingredient_nutrient_data[1]

            return nutrients
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
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

    @staticmethod
    def get_standardized_ingredients_nutrients_data(
        necess_nutrients_file: str,
        necess_nutrients_file_path: str,
        std_ingredients_nutrients_data: list[list[list[str, float]]]
    ) -> list[dict[str, float]] | None:
        """
        Returns an ingredients nutrients standardized data.

        :Parameters:
            necess_nutrients_file (str): A file with names of the necessary
                                         nutrients.
            necess_nutrients_file_path (str): A path to file with names of the
                                              necessary nutrients.
            std_ingredients_nutrients_data (list[list[list[str, float]]]):
                An ingredients nutrients data.

        :Returns:
            list[dict[str, float]]: An standardized ingredients nutrients data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            JSONDecodeError: When file data is not JSON format.
            Exception: All other errors.
        """

        try:
            with open(
                encoding="utf-8",
                file=necess_nutrients_file_path + necess_nutrients_file,
            ) as file:
                food_data: dict[str, list[str]] = load(file, )
                necess_nutrients: list[str] = food_data["nutrients"]

            res_ingredients_nutrients_data: list = []

            for std_ingredient_nutrients_data in std_ingredients_nutrients_data:
                res_ingredients_nutrients_data.append(
                    FDC.get_standardized_ingredient_nutrients_data(
                        necess_nutrients,
                        std_ingredient_nutrients_data,
                    ),
                )

            return res_ingredients_nutrients_data
        except JSONDecodeError as json_dec_err:
            raise JSONDecodeError(
                f"\nFile: {__file__}\n" +
                f"Message: {json_dec_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    @staticmethod
    def get_standardized_ingredients_nutrients_dataframe(
        necess_nutrients: list[str],
        std_ingredients_nutrients_data: list[dict[str, float]]
    ) -> DataFrame | None:
        """
        Returns an ingredients nutrients standardized Pandas dataframe.

        :Parameters:
            necess_nutrients (list[str]): A names of the necessary nutrients.
            std_ingredients_nutrients_data (list[dict[str, float]]):
                An standardized ingredients nutrients data.

        :Returns:
            DataFrame: An standardized ingredients nutrients Pandas dataframe.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            res_ingredients_nutrients_data: list = []

            for necess_nutrient, std_ingredient_nutrients_data in zip(
                necess_nutrients,
                std_ingredients_nutrients_data,
            ):
                std_ingredient_nutrients_data["name"] = necess_nutrient
                res_ingredients_nutrients_data.append(
                    std_ingredient_nutrients_data,
                )

            return DataFrame(res_ingredients_nutrients_data, )
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def set_configuration(self) -> None:
        """
        Sets the configuration for the class representative to work with the
        API.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            Exception: All other errors.
        """

        try:
            load_dotenv()

            self.config["URL"] = os.getenv("FDC_URL", )
            self.config["API_KEY"] = os.getenv("FDC_API_KEY", )
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

    async def fetch_ingredient_data(
        self,
        ingredient_name: str,
        async_client: AsyncClient
    ) -> dict[str, Any] | None:
        """
        Fetchs the ingredient data from the API.

        :Parameters:
            ingredient_name (str): An ingredient name to fetch from the API.
            async_client (AsyncClient): An asynchronous client for requests.

        :Returns:
            dict[str, Any]: An ingredient data from the API.
            None: If error occurs or no data is loaded.

        :Exceptions:
            JSONDecodeError: When file data is not JSON format.
            ConnectTimeout: When connection runtime is out.
            HTTPError: When HTTP error was raised.
            Exception: All other errors.
        """

        try:
            resp: Any = await async_client.get(
                self.config["URL"],
                params={
                    "pageSize": 1,
                    "query": ingredient_name,
                    "requireExactMatch": True,
                    "api_key": self.config["API_KEY"],
                },
            )

            if resp.status_code == 200:
                ingredient_data: dict[str, Any] = resp.json()

                return ingredient_data

            print(
                "ERROR!\n" +
                f"Ingredient: {ingredient_name}.\n" +
                f"Status code: {resp.status_code}.\n",
            )
        except JSONDecodeError as json_dec_err:
            raise JSONDecodeError(
                f"\nFile: {__file__}\n" +
                f"Message: {json_dec_err}.",
            )
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
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    async def fetch_ingredients_data(
        self,
        ingredients_names: list[str]
    ) -> list[dict[str, Any] | None] | None:
        """
        Fetchs the ingredients data from the API.

        :Parameters:
            ingredients_names (list[str]): An ingredients names to fetch from
                                           the API.

        :Returns:
            list[dict[str, Any] | None]: An ingredients data from the API.
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        ingredients_data: list = []

        try:
            self.set_configuration()

            async with AsyncClient() as async_client:
                for ingredient_name in ingredients_names:
                    ingredients_data.append(await self.fetch_ingredient_data(
                        ingredient_name,
                        async_client,
                    ), )

            return ingredients_data
        except ValueError as val_err:
            raise ValueError(
                f"\nFile: {__file__}\n" +
                f"Message: {val_err}.",
            )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )
