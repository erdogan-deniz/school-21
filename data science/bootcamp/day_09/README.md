# Advanced *machine learning*

Summary: today we will help master advanced tasks in *machine learning* in
*Python*.

## Foreword

There is real *data science* and *data science* for competitions.
The *data science*: in companies, you should have a broader skill set including
soft skills.
You need to understand the business, and to be focused on profit or the
organization’s other goals.
But in competitions, you simply need to be really good at achieving the
competition’s target metrics.
You may create a super heavy *machine learning* model that can be `0.00001`
better than the model of your next competitor and nobody cares how long it takes
to make predictions, how interpretable the model is, or how many computational
resources it requires.
In business all these criteria matter.
Nevertheless, you may use competitions for improving your skills.
The most popular platform is *Kaggle*.
It can be good for building your portfolio.
You can improve your collaboration skills.
The platform allows you to pursue the *machine learning* track as well as the
data exploration track: whatever you find more attractive.

## Exercise 00: models *regularization*

Turn-in directory: `ex_00/`

Files to turn in: `models_regularization.ipynb`

*Regularization* in its broader sense is a technique that prevents a model from
*overfitting*.
As regards *logistic regression*, we have a formula with different `X` and
coefficients.
*Regularization* penalizes coefficients that are too big making the formula more
robust and more ready for the unknown data that it will have to work with in the
future.
*L1 regularization* makes some coefficients equal to zero.
So this mode may be helpful for feature selection if there are lots of them and
you need to reduce the number.
*L2 regularization* does not make the weights equal to zero but may make them
smaller.
Usually, you need to try many different things on your dataset to find what
suits it best.
If we talk about trees and forests, *regularization* is connected to the
parameters that affect the number of cases in the leaves.
If your tree is so thick that each leaf includes only one sample, the chances
are that your tree has overfitted to the training dataset.
To prevent that, you can play with such parameters as `min_samples_split`,
`max_depth`, `min_samples_leaf`, `max_leaf_nodes`.
Many different algorithms have many different parameters of *regularization*.
You should just know that they exist, and if you need them, you will understand
how they work for a specific algorithm.

## Exercise 01: *gridsearch*

Turn-in directory: `ex_01/`

Files to turn in: `gridsearch.ipynb`

*GridSearch* is a way to automate hyper parameters.
You can specify the range of values for the parameters that you want to optimize
and put it to `GridSearchCV()`.
It will try all of them, calculate the metrics on *cross validation*, and give
you the best combination of parameters as well as the overall results of its
mini-research.

## Exercise 02: metrics

Turn-in directory: `ex_02/`

Files to turn in: `metrics.ipynb`

Imagine a situation in which you have two classes that are unbalanced: `95 %` of
the samples belong to the first class and `5 %` to the second.
The *accuracy* will be worse than a naive classifier when we make predictions
using the most popular class.
This case is quite popular for *anti-fraud* tasks.
The number of fraud cases is lower than the number of normal cases.
It is simple to understand and you can use it to compare different models within
a task, but this metric can be misleading when you need to compare the results
to a model from another task.
Also, it does not say much about the errors, you just know how many of them
there are.
All other metrics come from the *confusion matrix*.
The first is *precision*.
It is the number of correctly predicted samples of one class divided by the
number of predictions of that class.
Imagine that we predicted `10` days as a `weekend`, but only `7` of them were
really weekends.
The *precision* is `0.7`.
The second is *recall*.
This is the number of correctly predicted samples of one class divided by the
true number of that class.
Imagine that we predicted `10` days as a `weekend` but only `7` of them were
really weekends and in the dataset there were `20` weekends.
The *recall* is `0.35`.
*Precision* can be good when we want to show an ads that includes some `16+`
content.
We want to be precise in our prediction.
*Recall* can be good for identifying terrorists.
We may want to find them all no matter how many civilians experience some
inconvenience along the way.
There is also a metric that combines both of them in the *harmonic mean F1*
score.
You can use it when you need to optimize both of them.
Also, there is the *ROC-curve*.
When you make predictions, you usually you have probabilities.
And the final classification is *ade* by comparing them to the threshold.
If we see that, for that given day, the probability of being a weekend is `0.2`
and the threshold is `0.5`, we can say that it is not a `weekend`.
But if you change the threshold to `0.1`, the same sample will get the
prediction `weekend`.
Imagine now, that for each threshold we calculate *recall* and also the number
of how many working days we predicted as weekends divided by the real number of
working days.
We can put both those values on a plot and we will get the *ROC-curve*.
The higher it is, the better.
Comparing curves can be rather inconvenient.
That is why we can use another metric *AUC*.
*Precision*, *recall*, *AUC* are useful when we want to compare the performance
of different models from different tasks.
And they tell us something about the errors.
Everything that we told you here was connected to binary classification.
But it can be used with some adjustments for multiclass and multilabel
classification.

## Exercise 03: models ensembles

Turn-in directory: `ex_03/`

Files to turn in: `models_ensembles.ipynb`

You already know that a *random forest* is an ensemble of many different trees.
But actually you can create an ensemble from any type of model.
In this exercise, you will try several approaches: *voting classifier*,
*bagging classifier*, *stacking classifier*.

## Exercise 04: pipelines

Turn-in directory: `ex_04/`

Files to turn in: `pipelines.ipynb`

While trying to solve the problem you executed a lot of different actions:
prepared the data, tried different models, tried different metrics, optimized
their hyperparameters, tried different kinds of ensembles.
Now it probably looks a bit chaotic: your code is in different notebooks that
require a lot of scrolling.
In this exercise, the last of the day, you will make it look a bit cleaner, more
organized.
In real life, you may want to share it with your colleagues, you may want to
make it a part of your portfolio or it may be for your own future convenience.
The first part of your notebook will contain only the imports, classes and
methods.
The second part will be your "main program".
You will work with the initial data and you will go through most of the steps
that you executed before.
