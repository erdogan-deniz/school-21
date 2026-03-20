# Intro to *machine learning*

Summary: today we will help you with basic tasks involved in *machine learning*
in *Python*.

## Foreword

* There are a lot of different terms that are connected to the data field:
  *artificial intelligence*, *machine learning*, neural nets, *deep learning*.
* Each item of the list is a subset of the previous item.
  The broadest term is *artificial intelligence* includes any techniques that
  mimic human cognitive behavior.
  It can use *machine learning* algorithms in order to do this, or any other
  techniques like just writing a program with many `if-then-else` rules.
* *Machine learning* includes statistical algorithms that automate the process
  of creating the rules.
  The machine can find correlations and use them for different tasks by
  "looking" at the data.
* Neural nets are a subset of *machine learning* algorithms.
  They were created through the inspiration of how the human brain works.
* And *deep learning* algorithms are a subset of neural nets.
  They usually have many layers.
  That is why they are called "deep".
* Remember that none of these algorithms are limitless.
  They can help you only if you have the data.
  Simple algorithms can be satisfied with small amounts of data, and *deep*
  *learning* algorithms require large amounts of data.
  At the same time, if your data is garbage, the knowledge that you get from the
  algorithms will be garbage too.

## Exercise 00: binary *logistic regression* classifier

Turn-in directory: `ex_00/`

Files to turn in: `binary_logistic_regression_classifier.ipynb`

The following day, will cover some more sophisticated techniques.
First of all, *machine learning* can be divided into *supervised* and
*unsupervised*.
In *supervised learning*, you want to predict something.
In order to do that, you give the machine examples: a bunch of features and a
target variable.
Imagine that you want to predict whether a user would like or dislike a given
movie.
The features `X` can be: `genre`, `year_of_creation`, `budget`, `cast`,
`director`.
The target `Y` will be `like` or `dislike`.
That kind of task is a classification task.
In classification problems, `y` is always categorical.
If your target variable is continuous, it is called a regression problem.
*Unsupervised learning* does not require labels.
It does not forecast anything.
Usually, it helps you to understand your data better.
For example, clustering algorithms help you identify homogeneous groups of
observations.
You may find that you can divide your users into groups.
And for each of these groups create a special offer or a recommendation.
Do not confuse this with classification.
You are not trying to predict anything.
You are just looking at your data.
Besides clustering algorithms, *unsupervised learning* includes *dimensionality*
*reduction* algorithms.
They help you to reduce the number of features or observations.
It may be helpful if you have a lot of them, but you do not have sufficient
resources.
Also, they may help you to find some latent features and improve the quality of
your algorithms in *supervised learning*.
Let us to train a binary classifier which means that the target variable has
only two unique values.
You start from the *descriptive analysis* and proceed by analyzing some basic
statistics.
Then you go further and do *explorative analysis* by drawing different plots and
, as a result, get a better understanding of your data.
Only then do you move on to *predictive analysis* to forecast something.
In this exercise imagine the following situation.
From some moment in the past, you realized that the more data you collect, the
better.
And you started saving more fields in the logs.
Before, you had been collecting only the time of the commit.
But from that point in time, you started collecting the date too.
Now you need to train a classifier that can predict whether any given commit was
made during working days or during weekends.
Then you will be able to use the classifier to label the commits in the past
when you had not been collecting the data.
Every *supervised machine learning* algorithm requires at least two arguments:
`X` and `Y`.
`X` is the list of features and `Y` is the target column.
As you no doubt recall, we have logs like this `2020-04-17 05:19:02.744528`.
How can we use this to predict the type of weekday?
It is called *feature engineering*.
You need to extract these features from the logs.
So, we need to extract something that can somehow characterize days.
In this exercise, we will try a simple approach with only two features: the
number of commits before midday and the number of commits after midday.

## Exercise 01: binary classification models

Turn-in directory: `ex_01/`

Files to turn in: `binary_classification_models.ipynb`

Try to increase the quality of your classifier, and try other algorithms.
In this exercise you will see how *logistic regression* works.
Also, you will try two more *machine learning* algorithms: *SVM* and *decision*
*tree*.
You will visualize them too.

## Exercise 02: multiclass classification models

Turn-in directory: `ex_02/`

Files to turn in: `multiclass_classification_models.ipynb`

In real life, your target column may contain more than two values.
In such cases, you will need to train not a binary classifier, but a multiclass
classifier.
Also, you may have not only continuous features but categorical as well.
Algorithms understand numbers, they do not know what to do with text.
In this exercise, you will find out which features seem the most important for
different algorithms and you will try one more algorithm *random forest*.

## Exercise 03: *overfitting*

Turn-in directory: `ex_03/`

Files to turn in: `overfitting.ipynb`

Your models could just memorize all the observations.
In theory, you could achieve 100% accuracy, but would your model still be any
good if it tried to make predictions for data that it had not seen?
We highly doubt it.
That is called *overfitting*.
One of the techniques to prevent it is to make a train/test split.
You get a portion of data that you use for training, and another portion you use
to check the final quality of your model.
The second is *cross-validation*.
In this technique, we do not make a constant split, but we try different splits
and see what quality of predictions we get.

## Exercise 04: regression models

Turn-in directory: `ex_04/`

Files to turn in: `regression_models.ipynb`

Let us work on a regression problem in this exercise.
You will need to predict the average delta between the deadlines and the first
commit for every user with data about their views of the newsfeed and the number
of commits they made during the program.

## Exercise 05: clustering models

Turn-in directory: `ex_05/`

Files to turn in: `clustering_models.ipynb`

It is time to try using *unsupervised machine learning*.
This time we will work with clustering algorithms.
We will try to understand whether we can divide our users into some homogenous
groups for future analysis.
Maybe we can add some more triggers or engaging mechanics for them.
But the triggers and mechanics may differ depending on the users existing
behavior.
