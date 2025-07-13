"""
Plotting utilities.
"""


import matplotlib.pyplot as plt

from typing import Any
from numpy import ndarray
from pandas import DataFrame
from sklearn.metrics import silhouette_score


def draw_top_important_features(
    feat_names: ndarray | list,
    feat_importances: ndarray | list,
    top_size: int = 10
) -> None:
    """
    Visualizes top most important features as a horizontal bar plot.

    :Parameters:
        feat_names (ndarray | list): Array of feature names.
        feat_importances (ndarray | list): Array of feature importance scores.
        top_size: Number of top features to display.
                  Default: 10.
    """

    feat_df: DataFrame = DataFrame({
        "feature_name": feat_names,
        "feature_importance": feat_importances,
    }, ).sort_values(
        by="feature_importance",
        ascending=False,
    ).iloc[: top_size]

    feat_df[:: -1].plot.barh(
        x="feature_name",
        y="feature_importance",
    )
    plt.title("Features importances", )
    plt.xlabel("Feature importance",)
    plt.ylabel("Feature name", )
    plt.show()

def draw_clustering_model_parameter_optimization(
    X: DataFrame,
    opt_param: str,
    param_range: range,
    clusterer_model: object,
    model_params: dict[str, Any]
) -> None:
    """
    Optimizes and visualizes clustering performance across parameter values.

    :Parameters:
        X (DataFrame): Input feature matrix with shape.
        opt_param (str): Name of parameter to optimize.
        param_range (range): Range of parameter values to evaluate.
        clusterer_model (object): Uninitialized clustering model class.
        model_params (dict[str, Any]): Dictionary of fixed parameters for the
                                       clustering model.
    """

    silhouette_scores: list[float] = []
    best_param_val: None | float = None

    for param_val in param_range:
        model_params[opt_param] = param_val
        loc_clusterer_model: object = clusterer_model(**model_params, )
        silhouette_scores.append(
            silhouette_score(
                X,
                loc_clusterer_model.fit_predict(X, ),
            ),
        )

        if (best_param_val is None) or (
            silhouette_scores[-1] >= max(silhouette_scores, )
        ):
            best_param_val = param_val

    _, axs = plt.subplots(
        1,
        2,
        figsize=(14, 6, ),
    )

    axs[0].plot(
        param_range,
        silhouette_scores,
        marker='o',
        linestyle='-',
    )
    axs[0].set_xlabel(f"{opt_param} value", )
    axs[0].set_ylabel("Silhouette score", )
    axs[0].set_title(
        f"Silhouette score of clustering model with differents {opt_param} " +
        "parameter values",
    )

    model_params[opt_param] = best_param_val
    clusterer_model: object = clusterer_model(**model_params, )
    clusters_samples: ndarray = clusterer_model.fit_predict(X, )

    axs[1].scatter(
        X["num_commits"],
        X["AVG(diff)"],
        c=clusters_samples,
    )
    axs[1].set_xlabel("commits number", )
    axs[1].set_ylabel("AVG (difference)", )
    axs[1].set_title(
        f"Clustering model with parameter {opt_param} = {best_param_val}",
    )
    plt.show()
