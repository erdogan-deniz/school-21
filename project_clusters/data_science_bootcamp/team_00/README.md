# *MovieLens* analytics

Summary: this rush will help you to strengthen the skills acquired in the
previous days.

## Foreword

Why do we like movies?
What makes them so attractive to us?
Even though the movie is a relatively modern thing for humanity, it has a pretty
old mechanism inside – it is the story.
People have loved stories since ancient times.
Think about them as a universal container that effectively transfers some useful
information from a source to a person.
By sparkling emotions and imagination in us, it establishes a good connection
and packages information in a way that can be easily consumed by a human being.
Stories were crucial for surviving to our ancestors.
Stories contain the personal experience that can be applied to your life.
For example, you may discover that some areas around your village are pretty
dangerous.
Or there are some really good places to gather mushrooms.
Our attention to stories has survived through the centuries.
If a speaker starts their presentation by telling a story, they catch our
attention.
We love books.
We love music and songs.
We love movies.
How can you use stories in *data science*?
Good reports have elements of storytelling.
Try to tell a story by your analysis.

## Specific instructions for the day

* No code in the global scope.
* Any exception not caught will invalidate the work, even in the event of an
  error that was asked you to test.
* You can import the following modules: `os`, `re`, `sys`, `json`, `urllib`,
  `pytest`, `requests`, `datetime`, `functools`, `collections`, `beautifulsoup`.

## Mandatory part

In this rush, you are going to work on your own analytical report.
You will analyze data from the *MovieLens* database.
By the end of the rush, you will have module and file: `movielens_analysis` and
`movielens_report.ipynb`.
In the first, you will need to create your own module with classes and methods.
In the second file, you will create the report itself using only your module.

## Module

Remember that the goal of the rush is to strengthen your skills.
Try to use as much as you can from what you have learned from the previous days.

* read the `description.txt` very carefully.
  Focus on the file structures.
* use a smaller version of *MovieLens* dataset, download it, please.
  Try to use the first `1000` values from the dataset.
* in your module, you will need to create `5` classes corresponding to `5` files
  from the `data` and `5` class for testing.
* the classes and methods below are obligatory, but you can add to them anything
  that suits your needs.

Classes: `Tag`, `Link`, `User`, `Movie`, `Rating`.
Create tests using *PyTest* for each and every method of the classes above.
They should check:

* if the methods return the correct data types.
* if the lists elements have the correct data types.
* if the returned data sorted correctly.

## Report

Using only the classes and methods from `movielens_analysis.py`, prepare your
report.
You should do it in *Jupyter Notebook*.
It is a great tool especially if you are a data scientist.
It gives you an opportunity to work with the code interactively by launching and
relaunching different cells with different values.
You do not have to rerun your whole code from the beginning.
Also, you can put in the cells not only code but text too, which is a great
feature for making reports.
Install it to your environment.
In this part of the rush, we will give you more freedom.
We are not going to define the structure of your report.
The goal of the report is to tell us an interesting story about the *MovieLens*
dataset.
Find the good structure and the right sequence.
The only constraints:

* you must use each and every method from `movielens_analysis`.
* every cell in your notebook should contain magic command `%%timeit`.
* all other imports are prohibited as well as using built-in functions.
  If you need them, put them in your module in advance.

## Bonus part

* Add to the classes more methods that you may find useful and interesting for
  your report.
* Improve the tests.
  Check the correctness of your calculations as well.
  Precalculate manually some results and metrics and check if the methods return
  the correct information if you give them the specific input.
