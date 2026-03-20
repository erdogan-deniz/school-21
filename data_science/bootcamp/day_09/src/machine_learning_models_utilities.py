"""
Utilities for machine learning models.
"""


from pandas import DataFrame
from tqdm.notebook import tqdm
from typing import Any, Literal
from numpy import (
    ndarray,
    std,
    mean,
)
from sklearn.model_selection import (
    KFold,
    ParameterGrid,
    cross_val_score,
    train_test_split,
)
from sklearn.metrics import (
    recall_score,
    roc_auc_score,
    accuracy_score,
    precision_score,
)


def print_classification_model_cross_validation(
    classification_model: Any,
    X: DataFrame,
    y: ndarray,
    num_of_splits: int = 10,
    metric_name: Literal[
        "recall",
        "roc_auc",
        "accuracy",
        "precision",
    ] = "accuracy"
) -> None:
    """
    Prints K-Fold cross-validation results for a classification model.

    :Parameters:
        classification_model (Any): A compatible classifier.
        X (DataFrame): Feature matrix.
        y (ndarray): Target values.
        num_of_splits (int): Number of folds for K-Fold validation.
                             Default: 10.
        metric_name (Literal["recall", "roc_auc", "accuracy", "precision", ]):
            Evaluation metric to use.
            Default: "accuracy".

    :Exceptions:
        ValueError: When used invalid `metric_name` is provided.
        TypeError: When used model does not implement required methods.
        Exception: All other errors.
    """

    metric_vals: list[float] = []
    metrics_funcs: dict[str, function] = {
        "recall": recall_score,
        "roc_auc": roc_auc_score,
        "accuracy": accuracy_score,
        "precision": precision_score,
    }
    k_fold: KFold = KFold(
        shuffle=True,
        random_state=21,
        n_splits=num_of_splits,
    )

    try:
        for train_idx, test_idx in k_fold.split(X, ):
            X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
            y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

            classification_model.fit(X_train, y_train, )

            metric_vals.append(round(
                metrics_funcs[metric_name](
                    classification_model.predict(X_train, ),
                    y_train,
                ),
                3,
            ), )
            metric_vals.append(round(
                metrics_funcs[metric_name](
                    classification_model.predict(X_test, ),
                    y_test,
                ),
                3,
            ), )

            print(
                f"train {metric_name} - {
                    metrics_funcs[metric_name](
                        classification_model.predict(X_train, ),
                        y_train,
                    ):.3f
                }" +
                f" | test {metric_name} - {
                    metrics_funcs[metric_name](
                        classification_model.predict(X_test, ),
                        y_test,
                    ):.3f
                }",
            )

        print(f"\nClassification model STD is {std(metric_vals, ):.3f}.", )
        print(
            f"Classification model average {metric_name} on cross-validation " +
            f"is {(sum(metric_vals, ) / len(metric_vals, )):.3f}.\n",
        )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )


def get_classification_model_grid_search_results(
    classification_model: Any,
    X: DataFrame,
    y: ndarray,
    classification_model_params_grid: dict[str, Any],
    metric_name: Literal[
        "recall",
        "roc_auc",
        "accuracy",
        "precision",
    ] = "accuracy",
    num_of_splits: int = 5
) -> DataFrame | None:
    """
    Performs grid-search with cross-validation for a classification model and
    returns results.

    :Parameters:
        classification_model (Any): The classifier class.
        X (DataFrame): Feature matrix.
        y (ndarray): Target values.
        classification_model_params_grid (dict[str, Any]): Dictionary of
                                                           hyperparameters to
                                                           search.
        metric_name (Literal["recall", "roc_auc", "accuracy", "precision", ]):
            Evaluation metric to optimize.
            Default: "accuracy".
        num_of_splits (int): Number of cross-validation folds.
                             Default: 5.

    :Returns:
        DataFrame: Results sorted by mean metric.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid `metric_name` is provided.
        TypeError: When used model does not implement required methods.
        Exception: All other errors.
    """

    df_data: list[dict[str, Any]] = []
    classification_model_params_grid: list = list(ParameterGrid(
        classification_model_params_grid,
    ), )

    try:
        for classification_model_params in tqdm(
            classification_model_params_grid,
        ):
            loc_classification_model: Any = classification_model(
                random_state=21,
                **classification_model_params,
            )
            loc_classification_metric_scores: list[float] = cross_val_score(
                X=X,
                y=y,
                cv=num_of_splits,
                n_jobs=-1,
                scoring=metric_name,
                estimator=loc_classification_model,
            )

            df_data.append({
                **classification_model_params,
                f"std_{metric_name}": round(
                    std(loc_classification_metric_scores, ),
                    3,
                ),
                f"mean_{metric_name}": round(
                    mean(loc_classification_metric_scores, ),
                    3,
                ),
            }, )

        return DataFrame(
            df_data
        ).sort_values(
            ascending=False,
            by=[f"mean_{metric_name}", ],
        )
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )


def get_classification_models_metrics_values(
    classification_models: list[Any],
    classification_models_params: list[dict[str, Any]],
    X: DataFrame,
    y: ndarray
) -> dict[str, dict[str, float]] | None:
    """
    Evaluates multiple classification models and returns their performance
    metrics.

    :Parameters:
        classification_models (list[Any]): List of classifier classes to
                                           evaluate.
        classification_models_params (list[dict[str, Any]]): List of parameter
                                                             dictionaries for
                                                             each model.
        X (DataFrame): Feature matrix.
        y (ndarray): Target values.

    :Returns:
        dict[str, dict[str, float]]: Nested dictionary.
        None: If error occurs or no data is loaded.

    :Exceptions:
        ValueError: When used invalid `metric_name` is provided.
        TypeError: When used model does not implement required methods.
        Exception: All other errors.
    """

    classification_models_metrics_vals: dict[str, dict[str, float]] = {}
    X_train, X_test, y_train, y_test = train_test_split(
        X,
        y,
        stratify=y,
        test_size=0.2,
        random_state=21,
    )

    try:
        for classification_model, classification_model_params in zip(
            classification_models,
            classification_models_params,
        ):
            loc_classification_model: Any = classification_model(
                **classification_model_params,
            )

            loc_classification_model.fit(X_train, y_train, )

            classification_models_metrics_vals[
                str(loc_classification_model.__name__, )
            ] = {
                "accuracy": round(
                    accuracy_score(
                        loc_classification_model.predict(X_test, ),
                        y_test,
                    ),
                    3,
                ),
                "precision": round(
                    precision_score(
                        loc_classification_model.predict(X_test, ),
                        y_test,
                        average="weighted",
                    ),
                    3,
                ),
                "recall": round(
                    recall_score(
                        loc_classification_model.predict(X_test, ),
                        y_test,
                        average="weighted",
                    ),
                    3,
                ),
                "roc-auc": float(round(
                    roc_auc_score(
                        loc_classification_model.predict_proba(X_test, ),
                        y_test,
                        multi_class="ovo",
                        average="weighted",
                    ),
                    3,
                ), ),
            }

        return classification_models_metrics_vals
    except ValueError as val_err:
        print("ValueError:", val_err, )
    except TypeError as type_err:
        print("TypeError:", type_err, )
    except Exception as err:
        print("Exception:", err, )
