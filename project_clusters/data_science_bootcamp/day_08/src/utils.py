"""
Utility functions.
"""


from numpy import ndarray
from pandas import DataFrame
from sklearn.model_selection import KFold
from sklearn.metrics import root_mean_squared_error


def print_regression_model_cross_validation(
    X: DataFrame,
    y: ndarray,
    reg_model: object,
    n_splits: int = 10
) -> None:
    """
    Performs k-fold cross validation for a regression model and prints RMSE
    metrics.

    :Parameters:
        X (DataFrame): Feature matrix.
        y (ndarray): Target values.
        reg_model (object): Initialized regression model.
        n_splits (int): Number of folds for cross validation.
                        Default: 10.
    """

    k_fold: KFold = KFold(
        n_splits=n_splits,
        random_state=21,
        shuffle=True,
    )
    rmses: list[float] = []

    for train_idx, test_idx in k_fold.split(X, ):
        X_train, X_test = X.iloc[train_idx], X.iloc[test_idx]
        y_train, y_test = y.iloc[train_idx], y.iloc[test_idx]

        reg_model.fit(X_train, y_train, )
        rmses.append(
            round(
                root_mean_squared_error(
                    reg_model.predict(X_test, ),
                    y_test,
                ),
                3,
            ),
        )
        rmses.append(
            round(
                root_mean_squared_error(
                    reg_model.predict(X_train, ),
                    y_train,
                ),
                3,
            ),
        )
        print(
            f"train RMSE - {
                round(
                    root_mean_squared_error(
                        reg_model.predict(X_train, ),
                        y_train,
                    ),
                    3,
                )
            } " +
            f"| test RMSE - {
                round(
                    root_mean_squared_error(
                        reg_model.predict(X_test, ),
                        y_test,
                    ),
                    3,
                )
            }",
        )

    print(
        "Average RMSE on regression model cross validation is",
        round(
            sum(rmses, ) / len(rmses, ),
            3,
        ),
    )
