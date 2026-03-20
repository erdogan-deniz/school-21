"""
The launch point module of the nutriologist's app.
"""


from typing import Any
from pandas import DataFrame, read_csv

from models.nutritionist import Nutritionist
from utils import unpack_model, get_script_arguments


def main(
    model_file: str,
    model_file_path: str,
    features_file: str,
    features_file_path: str,
    food_recipes_file: str,
    food_recipes_file_path: str,
    recipes_descriptions_file: str,
    recipes_descriptions_file_path: str,
    ingredients_nutrients_percentage_file: str,
    ingredients_nutrients_percentage_file_path: str
) -> None:
    """
    Outputs the necessary data for the task.

    :Parameters:
        model_file (str): A machine learning model file for predicting the
                          rating of dishes.
        model_file_path (str): The path to the file of the machine learning
                               model for predicting the rating of dishes.
        features_file (str): A file with attributes for a machine learning
                             model.
        features_file_path (str): The path to the file with the attributes for
                                  the machine learning model.
        food_recipes_file (str): A file with recipes for dishes.
        food_recipes_file_path (str): The path to the recipe file.
        recipes_descriptions_file (str): A file with recipe description links.
        recipes_descriptions_file_path (str): The path to the file with recipe
                                              description links.
        ingredients_nutrients_percentage_file (str): A file with the percentage
                                                     information of the
                                                     nutrients of the
                                                     ingredients.
        ingredients_nutrients_percentage_file_path (str): The path to the file
                                                          with the percentage
                                                          information of the
                                                          nutrients of the
                                                          ingredients.

    :Exceptions:
        FileNotFoundError: When used file was not found.
        Exception: All other errors.
    """

    try:
        script_args: list[Any] | None = get_script_arguments()
        model: Any | None = unpack_model(model_file, model_file_path, )
        features: DataFrame = read_csv(features_file_path + features_file, )
        food_recipes: DataFrame = read_csv(
            food_recipes_file_path + food_recipes_file,
        )
        recipes_descriptions: DataFrame = read_csv(
            recipes_descriptions_file_path +
            recipes_descriptions_file,
        )
        ingredients_nutrients_percentage: DataFrame = read_csv(
            ingredients_nutrients_percentage_file_path +
            ingredients_nutrients_percentage_file,
        )
        nutritionist: Nutritionist = Nutritionist(
            model,
            features,
            food_recipes,
            recipes_descriptions,
            ingredients_nutrients_percentage,
        )
        pred_recipe_rating: float | None = nutritionist.predict_recipe_rating(
            script_args,
        )
        Nutritionist.print_predicted_recipe_rating(pred_recipe_rating, )
        nutritionist.print_ingredients_nutrients_facts(script_args, )
        nutritionist.print_top_three_similar_recipes(script_args, )
        nutritionist.print_menu_for_day()
    except FileNotFoundError as file_not_found_err:
        raise FileNotFoundError(
            f"\nFile: {__file__}\n" +
            f"Message: {file_not_found_err}.",
        )
    except Exception as err:
        raise Exception(
            f"\nFile: {__file__}\n" +
            f"Message: {err}.",
        )


if __name__ == "__main__":
    main(
        "classification_model.joblib",
        "models/",
        "features.csv",
        "data/datasets/processed/",
        "food_recipes.csv",
        "data/datasets/raw/",
        "recipes_descriptions.csv",
        "data/datasets/processed/",
        "ingredients_nutrients_percentage.csv",
        "data/datasets/processed/",
    )
