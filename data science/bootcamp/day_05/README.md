# Pandas: working with dataframes

Summary: today we will help you acquire skills with *Pandas*.

## Foreword

The name of *Pandas* is derived from the term "panel data", an econometrics term for data sets that include observations over multiple time periods for the same individuals.

## Exercise 00: load and save

Turn-in directory: `ex00/`

Files to turn in: `load_and_save.ipynb`

Allowed functions: `import pandas as pd`

In this exercise, you will need to load the [log file](https://drive.google.com/file/d/1kgByP3EZHL8xAm-oGaBpf0-fPdVIYRaY/view) into a dataframe, change the delimiter, and save it to another file.

* `read_csv()`:
  * filter the rows with index `2` and `3` using the argument `skiprows`, we know that these observations were fake.
  * filter the last `2` rows from the footer using the argument `skipfooter`, we know that these observations were fake too.
  * assign the following names to the column: `datetime`, `user`.
  * use `datetime` as the index column.
  * rename `datetime` to `date_time`.

* `to_csv()`:
  * use `;` as the delimiter.
  * save it to a file with the name `feed-views-semicolon.log`.

As the result of `read_csv()`, you need to achieve the following:

```jupyter
In [3]: df.head()
Out[3]:
user
datetime
2020-04-17 12:01:08.463179 artem
2020-04-17 12:01:23.743946 artem
2020-04-17 12:35:52.735016 artem
2020-04-17 12:36:21.401412 oksana
2020-04-17 12:36:22.023355 oksana

In [4]: df.tail()
Out[4]:
user
datetime
2020-05-21 16:36:40.915488 ekaterina
2020-05-21 17:49:36.429237 maxim
2020-05-21 18:45:20.441142 valentina
2020-05-21 23:03:06.457819 maxim
2020-05-21 23:23:49.995349 pavel
```

## Exercise 01: basic operations

Turn-in directory: `ex01/`

Files to turn in: `basic_operations.ipynb`

Allowed functions: `import pandas as pd`

In this exercise, you will work with a single log of users who visited a page, including their timestamps.

* create a dataframe `views` with two columns: `datetime`, `user` by reading `feed-views.log`:
  * convert the `datetime` to the `datetime64[ns]` Dtype.
  * extract: `year`, `month`, `day`, `hour`, `minute`, `second` from the values of that column to the new columns.

* create the new column `daytime`:
  * need to assign the particular time of day value if an `hour` is within a particular interval: 0 – 3.59 `night`, 4 – 6.59 `early morning`, 7 – 10.59 `morning`, 11 – 16.59 `afternoon`, 17 – 19.59 `early evening`, 20 – 23.59 `evening`.
  * use the method `cut` to solve this subtask.
  * assign the column `user` as the index.

* calculate the number of elements in your dataframe:
  * use the method `count()`.
  * calculate the number of elements in each time of day category using the method `value_counts()`.

* sort values in your dataframe by: `hour`, `minute`, `second` in ascending order.
* calculate the minimum and maximum for the `hour` and the mode for the `daytime` categories:
  * calculate the maximum of `hour` for the rows where the time of day is `night`.
  * calculate the minimum of `hour` for the rows where the time of day is `morning`.
  * find out who visited the page at those hours.
  * calculate the mode for the `hour` and `daytime`.

* show the `3` earliest hours in the `morning` and the corresponding usernames and the `3` latest hours and the usernames using `nsmallest()` and `nlargest()`.
* use the method `describe()` to get the basic statistics for the columns:
  * to find out what the most popular interval for visiting the page is, calculate the interquartile range for the `hour` by extracting values from the result of the `describe()` method and store it in the variable `iqr`.

## Exercise 02: preprocessing

Turn-in directory: `ex02/`

Files to turn in: `preprocessing.ipynb`

Allowed functions: `import pandas as pd`

One day you will train *machine learning* models, but most of them require the data to be clean and enriched: without duplicates or missing values.
*Pandas* gives you the tools not only to perform descriptive analysis and understand your data better but to preprocess it too.
That is what you are going to do in this exercise.

* [download](https://drive.google.com/open?id=1kFMUiXtrlw5B6WTjJ-mUm4-STV28Zsvn) and read the `.csv` file and make `ID` the index column.
* count the number of observations using the method `count()`.
* drop the duplicates, taking into account only the following columns: `CarNumber`, `Make_n_model`, `Fines`:
  * between the two equal observations, you need to choose the `last`.
  * check the number of observations again.

* work with missing values:
  * check how many values are missing from each column.
  * drop all the columns with over `500` missing values using the argument `thresh=`.
  * check how many missing values are in each column.
  * replace all the missing values in the `Refund` column with the previous value in that column for that cell, use the argument method.
  * check how many values are missing from each column.
  * replace all the missing values in the `Fines` column with the mean value of this column.
  * check how many values are missing from each column.

* split and parse the `Make` and `Model`:
  * use the method `apply()` both for splitting and for extracting the values to the new columns `Make` and `Model`.
  * drop the column `Make_n_model`.
  * save the dataframe in the *JSON* file `auto.json` in the format below:

```json
  [
    {"CarNumber": "Y163O8161RUS", "Refund": 2.0, "Fines": 3200.0, "Make": "Ford", "Model": "Focus"},
    {"CarNumber": "E432XX77RUS", "Refund": 1.0, "Fines": 6500.0, "Make": "Toyota", "Model": "Camry"},
  ]
```

## Exercise 03: selects and aggregations

Turn-in directory: `ex03/`

Files to turn in: `selects_n_aggs.ipynb`

Allowed functions: `import pandas as pd`

Ok, great.
Now we have cleaned our data: all the duplicates have been dropped, all the missing values have been deleted, and our columns have been reorganized to be more convenient for analysis.
Now we can go further.
We have a lot of questions that need to be answered.

* load the *JSON* file that you created in the previous exercise into a dataframe:
  * set `CarNumber` as the index column.

* make the following selects:
  * display the rows only where the `Fines` are more than `2,100`.
  * display the rows only where the `Fines` are more than `2,100` and the `Refund` equals `2`.
  * display the rows only where the `Model` are from the list: `````[’Focus’, ’Corolla’]`````.
  * display the rows only where the `CarNumber` is from the list: ```[’Y7689C197RUS’, ’92928M178RUS’, ’7788KT197RUS’, ’H115YO163RUS’, ’X758HY197RUS’]```.

* make the aggregations with the `Make` and the `Model`:
  * display the median `Fines` grouped by the `Make`.
  * display the median `Fines` grouped by the `Make` and the `Model`.
  * display the number of `Fines` grouped by the `Make` and the `Model` in order to understand if we can trust the median values.
  * display the minimum and the maximum `Fines` grouped by the `Make` and the `Model` in order to better understand the variance.
  * display the standard deviation of the `Fines` grouped by the `Make` and the `Model` in order to better understand the variance.

* make the aggregations with the `CarNumber`:
  * display the `CarNumber` grouped by the number of the `Fines` in descending order, we want to find those who most often violated the law.
  * select from the initial dataframe all the rows corresponding to the top `1` `CarNumber`, we want to zoom in a little bit.
  * display the `CarNumber` grouped by the sum of the `Fines` in descending order, we want to find those who paid the most.
  * select from the initial dataframe all the rows corresponding to the top `1` `CarNumber`, we want to zoom in a little bit.
  * display a table that answers the question: `Are there any car numbers that were connected to different models?`

## Exercise 04: enrichment and transformations

Turn-in directory: `ex04/`

Files to turn in: `enrichment.ipynb`

Allowed functions: `import pandas as pd`, `import numpy as np`, `import requests`

Cool.
But the more data you have the better the analysis you can conduct.
Let us enrich our initial dataset.

* read the *JSON* file that you saved in `ex02`:
  * one of the columns has the `float` type, so let us define the format of it in *Pandas* using `pd.options.display.float_format`: floats should be displayed with two decimals.
  * there are values missing from the `Model`, do not do anything with them.

* enrich the dataframe using a `sample` from that dataframe:
  * create a sample with `200` new observations with `random_state = 21`:
    * the sample should not have new combinations of the `CarNumber`, `Make`, `Model`, so the whole dataset will be consistent in these terms.
    * there are no restrictions on the `Refund` and `Fines`, you can take any value from these columns at random and use it towards any `CarNumber`.

  * concatenate the `sample` with the initial dataframe to a new dataframe `concat_rows`.

* enrich the dataframe `concat_rows` by a new column with the data generated:
  * create a *Pandas* series with the name `Year` using random integers from `1980` to `2019`.
  * use `np.random.seed(21)` before generating the years.
  * concatenate the series with the dataframe and name it `Year`.

* enrich the dataframe with the data from another dataframe:
  * create a new dataframe with the `CarNumber` and their owners:
    * get the most popular surnames in the *US*.
    * create a new series with the surnames from the data you gathered, the count should be equal to the number of unique `CarNumber` using the `sample`.
    * create the dataframe owners with `2` columns: `CarNumber`, `Surname`.

  * append `5` more observations to the `owners` dataframe.
  * delete the dataframe last `20` observations from the `owners` and add `3` new observations.
  * join both dataframes:
    * the new dataframe should have only the `CarNumbers` that exist in both dataframes.
    * the new dataframe should have all the `CarNumbers` that exist in both dataframes.
    * the new dataframe should have only the `CarNumbers` from the `concat_rows` dataframe.
    * the new dataframe should have only the `CarNumbers` from the `owners` dataframe.

* create a pivot table from the `concat_rows` dataframe, it should look like this, but with all the years:

    ![pivot-table](content/images/pivot_table.png)
* save both the `concat_rows` and `owners` dataframes to `.csv` files without an index.

## Exercise 05: Pandas optimizations

Turn-in directory: `ex05/`

Files to turn in: `optimizations.ipynb`

Allowed functions: `import pandas as pd`, `import gc`

We are returning to the idea of code efficiency.
By now you know the basics of *Pandas*.
It is time to get to know some cool stuff that most *Pandas* users neither use nor know about.

* read the `concat_rows.csv`.
* iterations: in all the following subtasks, you need to calculate `fines/refund*year` for each row and create a new column with the calculated data and measure the time using the magic command `%%timeit` in the cell:
  * loop: write a function that iterates through the dataframe using `for i in range(0, len(df, ), )`, `iloc[]` and `append()` to a list, assign the result of the function to a new column in the dataframe.
  * do it using `iterrows()`.
  * do it using `apply()` and `lambda` function.
  * do it using `Series` objects from the `dataframe`.
  * do it as in the previous subtask but with the method `.values`.

* indexing: measure the time using the magic command `%%timeit` in the cell:
  * get a row for a specific `CarNumber`, for example, `O136HO197RUS`.
  * set the index in your dataframe with `CarNumber`.
  * get a row for the same `CarNumber`.

* downcasting:
  * run `df.info(memory_usage=deep, )`, pay attention to the Dtype and the memory usage.
  * make a `copy()` of your initial dataframe into another dataframe optimized.
