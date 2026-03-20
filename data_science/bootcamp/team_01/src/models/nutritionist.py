"""
A module with model for the implementation of nutritionist services.

Examples of usage:
    >>> nutritionist: Nutritionist = Nutritionist(..., )

    >>> Nutritionist.print_predicted_recipe_rating(4.0, )
"""


import os
import sys

sys.path.append(
    os.path.dirname(
        os.path.abspath(__file__, ),
    ),
)

from typing import Any
from numpy import ndarray
from random import choice
from pandas import DataFrame
from sklearn.metrics.pairwise import cosine_similarity


class Nutritionist:
    """
    A nutritionist's class to receive his services.

    :Attributes:
            model (Any): A machine learning model for predicting the
                                rating of recipes.
            features (DataFrame): A signs for forecasting and analyzing
                                         recipes.
            food_recipes (DataFrame): A recipes data.
            recipes_descriptions (DataFrame): A data describing recipes.
            ingredients_nutrients_percentage (DataFrame):
                A percentage of nutrients for each ingredient.
    """

    def __init__(
        self,
        model: Any,
        features: DataFrame,
        food_recipes: DataFrame,
        recipes_descriptions: DataFrame,
        ingredients_nutrients_percentage: DataFrame
    ) -> None:
        """
        Initializes the "Nutritionist" class representative.

        :Parameters:
            model (Any): A machine learning model for predicting the
                                rating of recipes.
            features (DataFrame): A signs for forecasting and analyzing
                                         recipes.
            food_recipes (DataFrame): A recipes data.
            recipes_descriptions (DataFrame): A data describing recipes.
            ingredients_nutrients_percentage (DataFrame):
                A percentage of nutrients for each ingredient.
        """

        self.model: Any = model
        self.features: DataFrame = features
        self.food_recipes: DataFrame = food_recipes
        self.recipes_descriptions: DataFrame = recipes_descriptions
        self.ingredients_nutrients_percentage: DataFrame =\
            ingredients_nutrients_percentage

    @staticmethod
    def get_correct_ingridient_name(ingridient_name: str) -> str | None:
        """
        Returns the correct ingredient name.

        :Parameters:
            ingridient_name (str): An ingredient name.

        :Returns:
            str: A correct ingredient name.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            Exception: All other errors.
        """

        try:
            match ingridient_name.lower().strip():
                case "hominy" | "cornmeal" | "masa":
                    return "hominy/cornmeal/masa"
                case "jam" | "jelly":
                    return "jam or jelly"

            return ingridient_name
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
    def print_predicted_recipe_rating(pred_recipe_rating: float | None) -> None:
        """
        Prints an analytical opinion about the quality of the recipe.

        :Parameters:
            pred_recipe_rating (float | None): A predicted recipe rating.

        :Exceptions:
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        eval_val: str = ""

        print("\nI. THE FORECAST OF THE RECIPE RATING IS:", )

        try:
            match int(pred_recipe_rating, ):
                case 0:
                    eval_val = "terrible"
                case 1:
                    eval_val = "bad"
                case 2:
                    eval_val = "dubious"
                case 3:
                    eval_val = "normal"
                case 4:
                    eval_val = "good"
                case 5:
                    eval_val = "amazing"

            print(
                f"It is {eval_val} idea to have a dish with that list of " +
                "ingredients.",
            )
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

    def predict_recipe_rating(
        self,
        ingredients: list[str] | None
    ) -> float | None:
        """
        Predicts the recipe's rating by ingredients.

        :Parameters:
            ingredients (list[str] | None): A recipe ingredients.

        :Returns:
            float: The forecast of the recipe rating.
            None: If error occurs or no data is loaded.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            X: DataFrame = self.features.iloc[: 1].copy(
                deep=True,
            ).drop(
                columns="Unnamed: 0",
            )
            X.loc[0] = 0

            for ingredient in ingredients:
                if Nutritionist.get_correct_ingridient_name(
                    ingredient.lower().strip(),
                ) in X.columns:
                    X[
                        Nutritionist.get_correct_ingridient_name(
                            ingredient.lower().strip(),
                        )
                    ] = 1

            return self.model.predict(X, )[0]
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
            )
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

    def print_ingredient_nutrients_facts(self, ingredient: str) -> None:
        """
        Prints facts about the ingredient's nutrients.

        :Parameters:
            ingredient (str): An ingredient name.

        :Exceptions:
            AttributeError: When attribute is not initialized.
            IndexErroe: When used object do not has necessary index.
            Exception: All other errors.
        """

        try:
            print(ingredient.strip().capitalize() + ":", )

            ingredient = Nutritionist.get_correct_ingridient_name(ingredient, )
            ingredient_idx: int | None =\
                self.ingredients_nutrients_percentage.index[
                self.ingredients_nutrients_percentage["name"] == ingredient
            ]
            if not ingredient_idx.empty:
                for nutrient_name, nutrient_val \
                in self.ingredients_nutrients_percentage.iloc[
                    ingredient_idx[0]
                ][1: -1].items():
                    if nutrient_val > 0:
                        print(
                            f"  * {
                                nutrient_name.strip().capitalize()
                            } - {nutrient_val:.3f} % of daily value",
                        )
        except AttributeError as attr_err:
            raise AttributeError(
                f"\nFile: {__file__}\n" +
                f"Message: {attr_err}.",
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

    def print_ingredients_nutrients_facts(
        self,
        ingredients: list[str] | None
    ) -> None:
        """
        Prints facts about the ingredient's nutrients.

        :Parameters:
            ingredients (list[str] | None): An ingredients names.

        :Exceptions:
            TypeError: When used incorrect data types.
            Exception: All other errors.
        """

        print("\nII. THE FACTS OF INGREDIENTS NUTRIENTS ARE:", )

        try:
            for ingredient in ingredients:
                self.print_ingredient_nutrients_facts(ingredient, )
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

    def find_top_three_similar_recipes(
        self,
        ingredients: list[str]
    ) -> ndarray | None:
        """
        Returns the indexes of the top 3 recipes similar in cosine distance.

        :Parameters:
            ingredients (list[str]): An ingredients names.

        :Returns:
            ndarray: An indexes of similar strings
            None: If error occurs or no data is loaded.

        :Exceptions:
            ValueError: When used invalid data format.
            Exception: All other errors.
        """

        try:
            X: DataFrame = self.features.iloc[: 1].copy(
                deep=True,
            ).drop(
                columns="Unnamed: 0",
            )
            X.loc[0] = 0

            for ingredient in ingredients:
                if Nutritionist.get_correct_ingridient_name(
                    ingredient.lower().strip(),
                ) in X.columns:
                    X[
                        Nutritionist.get_correct_ingridient_name(
                            ingredient.lower().strip(),
                        )
                    ] = 1

            similarities: Any = cosine_similarity(
                X.values.reshape(1, -1, ),
                self.features.iloc[:, 1: ].values,
            )[0]

            return similarities.argsort()[-4: -1][:: -1]
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

    def print_top_three_similar_recipes(
        self,
        ingredients: list[str] | None
    ) -> None:
        """
        Prints the top 3 recipes from the collected ingredients.

        :Parameters:
            ingredients (list[str] | None): An ingredients names.

        :Exceptions:
            Exception: All other errors.
        """

        print("\nIII. TOP 3 SIMILAR RECIPES:", )

        try:
            for idx in self.find_top_three_similar_recipes(ingredients, ):
                print(
                    f"- {
                        self.recipes_descriptions.iloc[idx]["title"].strip()
                    }, rating: {
                        self.recipes_descriptions.iloc[idx]["rating"]
                    }, URL: {self.recipes_descriptions.iloc[idx]["url"]}",
                )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )

    def print_meal_info(self, meal_name: str) -> None:
        """
        Prints the food ration for the meal.

        :Parameters:
            meal_name (str): A name of the meal.

        :Exceptions:
            IndexError: When used incorrect index value.
            Exception: All other errors.
        """

        match meal_name:
            case "breakfast":
                meal_name = "BREAKFAST"
                recipe_idx: int = choice([
                    104,
                    108,
                    110,
                    132,
                    135,
                    144,
                    161,
                ], ) - 2
            case "lunch":
                meal_name = "LUNCH"
                recipe_idx: int = choice([
                    61,
                    69,
                    83,
                    98,
                    103,
                    122,
                    148,
                    158,
                ], ) - 2
            case "dinner":
                meal_name = "DINNER"
                recipe_idx: int = choice([
                    72,
                    87,
                    88,
                    94,
                    105,
                    123,
                ], ) - 2

        print(f"\n{meal_name}", )
        print("-------------------------------------------------------------", )

        nutrients_data: dict = {}
        ingredients_names: list = []

        try:
            print(
                f"{self.food_recipes.iloc[recipe_idx]["title"].strip()} " +
                f"(rating: {self.food_recipes.iloc[recipe_idx]["rating"]})" +
                "\nIngredients:",
            )

            for ingredient_name, val in self.features.drop(
                columns="Unnamed: 0",
            ).iloc[recipe_idx].items():
                if val:
                    print(f"- {ingredient_name}", )
                    ingredients_names.append(ingredient_name, )

            print("Nutrients:", )

            for ingredient_name in ingredients_names:
                ingredient_idx: int = self.ingredients_nutrients_percentage[
                    self.ingredients_nutrients_percentage["name"] ==\
                    ingredient_name
                ].index[0]

                for nutrient_name, val \
                in self.ingredients_nutrients_percentage.drop(
                    columns=["name", "Unnamed: 0", ],
                ).iloc[ingredient_idx].items():
                    if val:
                        nutrients_data[nutrient_name] = nutrients_data.get(
                            nutrient_name,
                            0,
                        ) + val

            for nutrient_name, val in nutrients_data.items():
                print(f"- {nutrient_name}: {val:.1f} %", )

            print(f"URL: {self.recipes_descriptions["url"].iloc[recipe_idx]}", )
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

    def print_menu_for_day(self) -> None:
        """
        Prints the optimal diet for the day.

        :Exceptions:
            Exception: All other errors.
        """

        print("\nIV. MENU FOR A DAY:", )

        try:
            self.print_meal_info("breakfast", )
            self.print_meal_info("lunch", )
            self.print_meal_info("dinner", )
        except Exception as err:
            raise Exception(
                f"\nFile: {__file__}\n" +
                f"Message: {err}.",
            )
