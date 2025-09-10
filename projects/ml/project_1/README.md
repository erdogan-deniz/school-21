# *Machine Learning* introduction

Summary: the project is introduction into *Machine Learning* and *data analysis*
with practical.

## Foreword

"With the increasing amounts of data in electronic form, the need for automated
methods for *Data Analysis* grow.
*Machine Learning* is methods that automatically detect patterns in data, use
the uncovered patterns to predict future data or for other." - the definition of
*Machine Learning* from the book - "*Machine Learning* A Probabilistic
Perspective" by *Kevin P. Murphy*.

A problems that are solved with *Machine Learning* methods:

* The problem of housing price prediction.
  We are trying to define a cost of an object with set of features.
* What disease does the patient have if we observe a set of symptoms?
* Will the client of the bank return the loan if his income is `X` and he has a
  good credit history?
* What products to show for users on the page of the online store to speed up
  search?

A machine solve this problems without prejudice and faster then people.
Data calls for automated methods of analysis, which *Machine Learning* provides.

## Stages of model building

You know about the estate market (*features*) and understand how the price
depends on factors (algorithm).
First, you split the houses into two groups: **train** and **test** data.
*Train* is used to determine relations between features and price.
*Test* predicts the price for houses, which are not in *train*.
*Building a model* is a sequence of methods: to prepare and analyze data, find
relations, then predict prices.
First step is capture patterns from *train* data is **fitting**/**training**
the model.
The data used to fit the model is the **training data**.
All the characteristics on which base decision are **features**, for example,
the number of bedrooms.
A price is the **target**.
After the model has been fit, apply it to new or *test* data to **predict**
prices of houses.
This allow to understand how the model performs on unseen data, evaluate model's
performance.
Are the model's predictions close to what actually?

Follow the next steps to build *Machine Learning* model:

1. Collect *training data*
2. Get *features* and *target*
3. *Train* model
4. Get predictions on *features* from unseen dataset (*test data*)
5. Evaluate quality of the model

## *Machine Learning* algorithms

*Tom Mitchell’s* definition of *Machine Learning*: "A program learns from
experience *E* with respect to some class of tasks *T*, and performance measure
*P*, if its performance at tasks in *T*, as measured by *P*, improves with
experience *E*."
The definition is close to children’s experience (*E*) in school.
Childrens learns a multiplication table (*T*) and gets grades
(*P*) for knowledge.
The more times children repeat a multiplication table, the more improved their
knowledge and better grades they achieve.
There are kinds of *Machine Learning*, depending on the nature of the task (*T*)
the system to learn, the nature of the performance measure (*P*) use to evaluate
the system, the nature of the experience (*E*) we give it.
We can change the conditions of the task and it require another solution.
The *Machine Learning* methods classification is into **Supervised Learning**
and **Unsupervised Learning**.

### *Supervised Learning*

*Supervised Learning* is when input variables `X` and an output `y`, and use an
algorithm to learn the mapping from the input to the output.
The housing price prediction is an *Supervised Learning* problem.
It is *Supervised Learning* the process of an algorithm learning from the
training dataset, as a teacher supervising the learning process.
We know the answers, the algorithm iteratively makes predictions on the training
data and is corrected.
Learning stops when the algorithm achieves an level of performance.
*Supervised Learning* grouped into **Regression** and **Classification**.

#### *Classification*

In classification, the output is a set of *C* exclusive labels known as
**classes**, `Y = {1, 2, 3, ..., C}`.
The predicting the class label given an input is called **Pattern Recognition**.

##### **Binary Classification**

If there are two classes, often denoted by:d `y = {0, 1}` or `y = {−1, 1}` it is
**Binary Classification**.
For example, to answer the question: "Has the patient a heart disease?"

##### **Multiclass Classification**

A classification with several classes (`> 2`) is **Multiclass Classification**.
*Multiclass Classification* is used when each sample is one class: a fruit is an
apple or a pear or a banana, but not at the same time.

#### **Regression**

*Regression* is to predict a real-valued quantity `y ∈ R`.

### *Unsupervised Learning*

*Unsupervised Learning* is get observed **inputs**
`D = {xn: n {1, 2, 3, ..., N}}` without corresponding **output** `yn`.
*Unsupervised Learning* is when you have *input* data `X` and do not have
corresponding *output* variables.
*Unsupervised Learning* grouped into **Clustering**, **Association**,
**Dimensionality Reduction**.

#### *Clustering*

A *Clustering* is discover the inherent groupings in the data, such as grouping
customers by purchasing behavior.

#### *Association*

An *Association* is where you want to discover rules that describe portions of
data, such as people that buy `A` also tend to buy `B`.

#### *Dimensionality Reduction*

*Dimensionality Reduction* is to detect properties in dataset and at the same
time understand which features differ a lot.
When we have features we can use such information to compress features to
smaller amounts and not to lose crucial information inside.
This is useful when need to visualize dataset with many features.
There are the basics of *Machine Learning* theory.

## Tasks

Solve a problem from `Kaggle.com`.
You will predict the price of an apartment rental listing based on the listing
content: text description, photos, number of bedrooms, price.
The data comes from `renthop.com`, an apartment listing website.

Follow instructions:

1. Analysis:
   1. Write `5` examples of *Machine Learning* methods application in life.
      What is the benefit of using *Machine Learning* methods?
   2. Classify tasks from table and examples to define their class.
   3. Write the difference between *Multiclass Classification* and *Multilabel*
      *Classification*.
   4. Is an case with housing prices a regression problem?
   5. Is it possible to reduce the regression problem to classification?

2. *Data Analysis*:
   1. Import *Python* libraries:
      `pandas`, `numpy`, `sklearn`, `lightgbm`, `scipy`, `statsmodels`,
      `matplotlib`, `seaborn`.
      Use `pip install -r requirements.txt`.
   2. Load data from `Kaggle.com` with *Pandas*.
      You are need `train.json`.
   3. What is the size of data?
   4. Print the list of columns.
      Which column is a target?
   5. Make an analysis of the data:
      Use methods `info()`, `describe()`, `corr()`.
      Explain the results of outputs.
      Are there empty columns?
   6. Work with `3` features:
      `bathrooms`, `bedrooms`, `interest_level` with target column `price`.
      Make a *Pandas* dataframe with these columns.

3. *Statistical Data Analysis*:
   1. Give a definition of: *mean*, *median*, *mode*, *variance*, *standard*
      *deviation*, *outliers*, *percentiles*, *confidential intervals*.
      Give a definition of distributions: *Discrete uniform*, *Distribution*,
      *Bernoulli Distribution*, *Binomial Distribution*, *Poisson Distribution*,
      *Normal Distribution*, *Exponential Distribution*.
   2. Read this [Web-site](https://towardsdatascience.com/how-to-compare-two-or-more-distributions-9b06ee4d30bf)
      about *A/B Test*.
   3. Target analysis:
      * Plot a distribution histogram of the target `price`.
        Is it clear?
      * Plot the boxplot.
        What you say about target?
        Are there outliers?
      * Drop rows which are out of the `1` and `99` percentile by the target
        column.
      * Plot a histogram for target `price` again.
        Explain the result.

   4. Features analysis:
      * What is the type of column `interest_level`?
      * Print the values of column `interest_level`.
        How many items each value contains?
      * Decode these values.
        For example, replace each value to: `0`, `1`, `2`.
      * Plot histograms for features: `bathrooms`,  `bedrooms`.
        Are there outliers?

   5. Complex analysis:
      * Plot a correlation matrix to understand correlation.
        Plot a *heatmap* plot for correlation matrix.
        Is there a correlation?
      * Use a *scatter* plot to visualize correlation between features and
        target.
        You should return `3` plots, where `X` axis it target, and `Y` axis is a
        feature.

4. Generate features:
   1. Add `3` features, which are squared: `bathrooms_squared`,
      `bedrooms_squared`, `interest_level_squared`.
      Plot a correlation matrix with features.
      Are new features more correlated with target then basic features?
   2. To train the model, we will consider: `bathrooms`, `bedrooms` features.
   3. Read this *sklearn* info about `PolynomialFeatures()`:
      <https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.PolynomialFeatures.html>
   4. Split data to *train* and *test* samples.
      Read the train and test data.
   5. Initialize `PolynomialFeatures()` with the degree of `10`.
   6. Apply `PolynomialFeatures()` to fit and transform train and test data.

5. Train `3` models: *linear regression*, *decision tree*, native model:
   1. Result table:
      * Create two *Pandas* dataframe's with columns: `model`, `train`, `test`.
        The first be called `result_MAE`, the second `result_RMSE`.
   2. *Linear Regression*:
      * Initialize *Linear Regression* without parameters.
      * Fit model and make predict on train and test features.
      * Save it as columns in data.
      * Calculate *MAE* (Mean Absolute Error) on train and test targets.
      * Calculate *RMSE* (Root Mean Square Error) on train and test targets.
      * Insert metrics into tables *result_MAE* and *result_RMSE* with model
        name `linear_regression`.

   3. *Decision Tree*:
      * Initialize *decision tree* regressor from *sklearn* with
        `random_state=42`.
      * Fit it on train features and train target and make predict on train and
        test features.
      * Save it as new column in data.
      * Calculate *MAE* (Mean Absolute Error) on train and test targets.
      * Calculate *RMSE* (Root Mean Square Error) on train and test targets.
      * Insert metrics into tables *result_MAE* and *result_RMSE* with model
        name `decision_tree`.

   4. Native models:
      * Calculate mean and median of `price` on train and test data and create
        a columns with these values.
      * Calculate *MAE* on train and test targets between target and calculated
        mean and median values.
      * Calculate *RMSE* on train and test targets between target and calculated
        mean and median values.
      * Insert metrics into tables `result_MAE` and `result_RMSE` with model
        names `native_mean` and `native_median`.

   5. Compare results:
      * Print final tables `result_MAE` and `result_RMSE`.
      * What is the best model?

   6. Additional:
      * You may practice with all data in start dataset.
        Use and generate all features you want.

## Submission

Save code in *Python* *Jupyter Notebook*.
Peer will load it and compare with basic solution.
Code should contain the answers to all mandatory questions.
Task `additional` is on your own.
