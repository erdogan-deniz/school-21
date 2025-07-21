"""
A collection of components for building machine learning pipelines.
"""


from typing import Any
from joblib import dump
from tqdm.notebook import tqdm
from numpy import ndarray, prod
from pandas import DataFrame, concat
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import OneHotEncoder
from sklearn.base import BaseEstimator, TransformerMixin
from sklearn.model_selection import GridSearchCV, train_test_split


class FeatureExtractor(BaseEstimator, TransformerMixin):
    """
    A feature engineering class for extracting features from Pandas dataframe.

    :Attributes:
        df (DataFrame | None): Pandas dataframe data.
                               Default: None.
    """

    def __init__(
        self,
        df: DataFrame | None = None
    ) -> None:
        """
        Initializes `FeatureExtractor` with data.

        :Parameters:
            df (DataFrame | None): Pandas dataframe data.
        """

        self.df: DataFrame | None = df

    def fit(
        self,
        X: DataFrame,
        y: ndarray | None = None
    ) -> None:
        """
        Fits the transformer to the data.

        :Parameters:
            X (DataFrame): Input features to fit on.
            y (ndarray | None): Target values.
                                Default: None.
        """

        self.df = X

        return self

    def exctract_hours_from_timestamps(self) -> None:
        """
        Extracts `hour` component from `timestamp` column.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.df["hour"] = self.df["timestamp"].dt.hour
        except Exception as err:
            print(err, )

    def exctract_weekdays_from_timestamps(self) -> None:
        """
        Extracts `weekday` component from `timestamp` column.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.df["weekday"] = self.df["timestamp"].dt.day_of_week
        except Exception as err:
            print(err, )

    def drop_columns(self, cols_names: list[str] = ["timestamp", ]) -> None:
        """
        Removes columns from the Pandas dataframe.

        :Parameters:
            cols_names (list[str]): List of columns names to drop.
                                    Default: ["timestamp", ].

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.df = self.df.drop(columns=cols_names, )
        except Exception as err:
            print(err, )

    def process_dataframe(self) -> None:
        """
        Executes full feature extraction pipeline.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.exctract_hours_from_timestamps()
            self.exctract_weekdays_from_timestamps()
            self.drop_columns()
        except Exception as err:
            print(err, )

    def transform(self, X: DataFrame | None = None) -> DataFrame | None:
        """
        Returns processed Pandas dataframe with extracted features.

        :Parameters:
            X (DataFrame | None): Input features to fit on.
                                  Default: None.

        :Returns:
            DataFrame: Processed Pandas dataframe with features.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.process_dataframe()

            return self.df
        except Exception as err:
            print(err, )


class MyOneHotEncoder(BaseEstimator, TransformerMixin):
    """
    A custom one-hot encoder for features in Pandas dataframe.

    :Attributes:
        target_col_name (str): Name of the target column.
        df (DataFrame | None): Pandas dataframe with features.
                               Default: None.
    """

    def __init__(
        self,
        target_col_name: str,
        df: DataFrame | None = None
    ) -> None:
        """
        Initializes `MyOneHotEncoder` with the data and target column name.

        :Parameters:
            target_col_name (str): Name of the target column.
            df (DataFrame | None): Pandas dataframe with features.
                                   Default: None.
        """

        self.df: DataFrame | None = df
        self.target_col_name: str = target_col_name

    def fit(
        self,
        X: DataFrame,
        y: ndarray | None = None
    ) -> None:
        """
        Fits the transformer to the data.

        :Parameters:
            X (DataFrame): Input features to fit on.
            y (ndarray | None): Target values.
                                Default: None.
        """

        self.df = X

        return self

    def get_categorical_features_names(self) -> list[str] | None:
        """
        Identifies categorical features in the Pandas dataframe.

        :Returns:
            list[str]: List of categorical column names.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            df: DataFrame = self.df

            if self.target_col_name in df.columns:
                df = df.drop(self.target_col_name, )

            return df.select_dtypes(
                include=[
                    "object",
                    "string",
                    "category",
                ],
            ).columns.tolist()
        except Exception as err:
            print(err, )

    def transform_categorical_features(self) -> None:
        """
        Applies one-hot encoding to categorical features.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            one_hot_encoder: OneHotEncoder = OneHotEncoder(
                sparse_output=False,
            )
            encoded_df: DataFrame = DataFrame(
                one_hot_encoder.fit_transform(
                    self.df[self.get_categorical_features_names()],
                ),
                columns=one_hot_encoder.get_feature_names_out(
                    input_features=self.get_categorical_features_names(),
                ),
                index=self.df.index,
            )
            self.df = concat([self.df, encoded_df, ], axis=1, )
        except Exception as err:
            print(err, )

    def drop_columns(self, cols_names: list[str]) -> None:
        """
        Removes columns from the Pandas dataframe.

        :Parameters:
            cols_names (list[str]): List of columns names to drop.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.df = self.df.drop(columns=cols_names, )
        except Exception as err:
            print(err, )

    def process_categorical_features(self) -> None:
        """
        Executes the complete feature processing pipeline.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.transform_categorical_features()
            self.drop_columns(self.get_categorical_features_names(), )
        except Exception as err:
            print(err, )

    def transform(
        self,
        X: DataFrame | None= None
    ) -> DataFrame | None:
        """
        Returns processed features.

        :Parameters:
            X (DataFrame | None): Input features to fit on.
                                  Default.

        :Returns:
            DataFrame: Features data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.process_categorical_features()

            return self.df
        except Exception as err:
            print(err, )


class TrainValidationTest:
    """
    Utility class for splitting data into train, validation, test sets.

    :Attributes:
        X (DataFrame): Feature matrix.
        y (ndarray): Target array.
    """

    def __init__(
        self,
        X: DataFrame,
        y: ndarray
    ) -> None:
        """
        Initializes `TrainValidationTest` with data.

        :Parameters:
            X (DataFrame): Feature matrix.
            y (ndarray): Target array.
        """

        self.X: DataFrame = X
        self.y: ndarray = y

    def get_train_validation_test_data(self) -> tuple[list] | None:
        """
        Splits data into train, validation, test sets.

        :Returns:
            tuple[list]: Train, validation, test data.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            X_temp, X_test, y_temp, y_test = train_test_split(
                self.X,
                self.y,
                test_size=0.2,
                stratify=self.y,
                random_state=21,
            )
            X_train, X_valid, y_train, y_valid = train_test_split(
                X_temp,
                y_temp,
                stratify=y_temp,
                test_size=0.125,
                random_state=21,
            )

            return X_train, X_valid, X_test, y_train, y_valid, y_test
        except Exception as err:
            print(err, )


class ModelSelection:
    """
    Utility class for comparing and selecting the best classification model
    through grid search.

    :Attributes:
        grid_searches (list[GridSearchCV]): Stores the grid search objects.
        models_data (dict[int, str]): Models names dictionary.
    """

    def __init__(
        self,
        grid_searches: list[GridSearchCV],
        models_data: dict[int, str]
    ) -> None:
        """
        Initializes `ModelSelection` with grid searches and model data.

        :Parameters:
            grid_searches (list[GridSearchCV]): Stores the grid search objects.
            models_data (dict[int, str]): Models names dictionary.
        """

        self.grid_searches: list[GridSearchCV] = grid_searches
        self.models_data: dict[int, str] = models_data

    def get_best_classification_model_name(
        self,
        X_train: DataFrame,
        y_train: ndarray,
        X_valid: DataFrame,
        y_valid: ndarray
    ) -> str | None:
        """
        Identifies the best performing classification model based on validation
        score.

        :Parameters:
            X_train (DataFrame): Training features.
            y_train (ndarray): Training targets.
            X_valid (DataFrame): Validation features.
            y_valid (ndarray): Validation targets.

        :Returns:
            str: Name of the best performing classification model.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        best_classification_model_name: str = None
        best_classification_model_score: float = 0.0

        try:
            for idx, grid_search in enumerate(self.grid_searches, ):
                print(f"\nEstimator is {self.models_data[idx]}:", )

                fits_cnt: int = prod([
                    len(params, )
                    for params
                    in grid_search.param_grid.values()
                    ], ) * 2

                with tqdm(
                    ncols=1000,
                    unit="s",
                    total=fits_cnt,
                    desc=f"{self.models_data[idx]}",
                ) as progress_bar:
                    grid_search.fit(X_train, y_train, )

                    loc_score: float = grid_search.score(X_valid, y_valid, )

                    if loc_score > best_classification_model_score:
                        best_classification_model_score = loc_score
                        best_classification_model_name = self.models_data[idx]

                    progress_bar.update(fits_cnt, )

                    print(
                        "Best classification model parameters are " +
                        f"{grid_search.best_params_}.",
                    )
                    print(
                        f"Classification model training accuracy metric is {
                            grid_search.best_score_:.3f
                        }.",
                    )
                    print(
                        "Classification model validation accuracy metric " +
                        f"is {loc_score:.3f}.",
                    )

            print(
                "\nClassification model with best validation accuracy " +
                f"metric is {best_classification_model_name}.",
            )

            return best_classification_model_name
        except Exception as err:
            print(err, )

    def get_the_best_classification_models_results(
        self,
        X_train: DataFrame,
        y_train: ndarray,
        X_valid: DataFrame,
        y_valid: ndarray
    ) -> DataFrame | None:
        """
        Generates comparison Pandas dataframe of all models performance.

        :Parameters:
            X_train (DataFrame): Training features.
            y_train (ndarray): Training targets.
            X_valid (DataFrame): Validation features.
            y_valid (ndarray): Validation targets.

        :Returns:
            DataFrame: Classification models results.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        models_names: list[str] = []
        models_params: list[dict[str, Any]] =  []
        models_scores: list[float] = []

        try:
            for idx, grid_search in enumerate(self.grid_searches, ):
                loc_model_name: str = self.models_data[idx]

                grid_search.fit(X_train, y_train, )
                models_names.append(loc_model_name, )
                models_params.append(grid_search.best_params_, )
                models_scores.append(grid_search.score(X_valid, y_valid, ), )

            return DataFrame({
                "model": models_names,
                "parameters" : models_params,
                "validation_score": models_scores,
            }, )
        except Exception as err:
            print(err, )


class Finalize:
    """
    Utility class for final model evaluation and persistence.

    :Attributes:
        classification_model (Any): A trained compatible classifier model.
    """

    def __init__(self, classification_model: Any) -> None:
        """
        Initializes `Finalize` with a trained classification model.

        :Parameters:
            classification_model (Any): A trained classifier model.
        """

        self.classification_model: Any = classification_model

    def get_final_score(
        self,
        X_train: DataFrame,
        y_train: ndarray,
        X_test: DataFrame,
        y_test: ndarray
    ) -> float | None:
        """
        Evaluates and returns the classification model's accuracy metric on test
        data.

        :Parameters:
            X_train (DataFrame): Training features.
            y_train (ndarray): Training targets.
            X_test (DataFrame): Test features for evaluation.
            y_test (ndarray): True labels for test set.

        :Returns:
            float: Accuracy metric score.
            None: If error occurs or no data is loaded.

        :Exceptions:
            Exception: All other errors.
        """

        try:
            self.classification_model.fit(X_train, y_train, )

            print(
                f"Accuracy metric of the classification model is {
                    accuracy_score(
                        self.classification_model.predict(X_test, ),
                        y_test,
                    ):.3f
                }.",
            )

            return round(
                accuracy_score(
                    self.classification_model.predict(X_test, ),
                    y_test,
                ),
                3,
            )
        except Exception as err:
            print(err, )

    def save_classification_model(
        self,
        classification_model_path: str = "../../models/"
    ) -> None:
        """
        Serializes and saves the classification model.

        :Parameters:
            classification_model_path (str): Destination path for model
                                             serialization.
                                             Default: "../../models/".

        :Exceptions:
            Exception: All other errors.
        """

        try:
            dump(
                self.classification_model,
                classification_model_path,
            )
            print(
                "Classification model was successfuly saved:" +
                f" {classification_model_path}.",
            )
        except Exception as err:
            print(err, )
