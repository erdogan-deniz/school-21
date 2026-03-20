# *Pandas*, *SQL* and data visualization

Summary: today we will help you with data visualization in *Matplotlib*, *Seaborn*, *Plotly*.

## Foreword

Visualization is good for two reasons.
The first, it is very useful when you need to communicate your results to somebody: your employer, colleagues, customers.
Second, it is useful building for a better understanding of the data.
Here is an example that shows why it is important.
Try to imagine or use a piece of paper to graph the distribution of two variables with the following characteristics.
![1](content/images/1.png)

Do you think that there is only one way to place the dots?
No, there are several.
It is called [Anscombe’s quartet](https://en.wikipedia.org/wiki/Anscombe's_quartet).
![2](content/images/2.png)

All of the graphs above have the same characteristics.
Can you believe it?
Looking at the characteristics alone can be misleading.
Use graphs to understand the data better.

## Exercise 00: line chart

Turn-in directory: `ex_00/`

Files to turn in: `00_line_chart.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`

Today, you will work with the same datasets that you used on the previous day.
We will try to understand the data about how the students of the educational company behave.
You will use *Pandas* and *SQL* again to sharpen your skills and use various libraries for data visualization in *Python*: *Matplotlib*, *Seaborn*, *Plotly*.
As usual, let us start with something simple.
If you have not drawn a graph in *Python*, it is time to do it for the first time.
Remember how we analyzed the newsfeed page?
Did you wonder how often the page was visited in time?

* make a connection to the [database](https://drive.google.com/open?id=1zQ8AR2Ry3ajzB3UZO1Sfk3xtDJlzQF2M).
* run a query that gets the `datetime` from the `pageviews` table, selecting only the users and not the admins.
* using *Pandas*, create a new dataframe where the `visits` are counted and grouped by `date`.
* using *Pandas* method `.plot()`, create a graph:
  * the size of the font should be `8`.
  * the size of the figure is `(16, 8)`.
  * the graph must have the title `Views per day`.
  * notice the rotation of `xticks` on the graph below.
    ![3](content/images/3.png)

* close the connection to the database.

## Exercise 01: line chart with styles

Turn-in directory: `ex_01/`

Files to turn in: `01_line_chart_styles.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`

Cool!
Remember that we have the data about the commits?
Wouldn’t it be cool to draw both of the metrics in time on the same graph?
What if we will see some patterns?
You need to create exactly the same graph as below:
![4](content/images/4.png)

* analyze only the users and not the admins.
* analyze only the dates when there were both views and checker commits.
* use size of the font should be `8`.
* the size of the figure is `(16, 8)`.
* at the end of *Jupyter Notebook* create a markdown cell and insert the question:
  `"How many times was the number of views larger than 150?"`

## Exercise 02: bar

Turn-in directory: `ex_02/`

Files to turn in: `02_bar_chart.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`

We have another question for you to answer: `when do our users usually commit the labs: in the night, morning, afternoon, or evening?`
And how has it changed over time?
Do what you need to do to create a graph like this:

![5](content/images/5.png)

* analyze only the users and not the admins.
* night is from `0:00:00` to `03:59:59`, morning is from `04:00:00` to `09:59:59`, afternoon is from `10:00:00` to `16:59:59`, evening is from `17:00:00` to `23:59:59`.
* the `fontsize=` and the `figsize=` are still the same.
* choose a palette that you really enjoy, you do not have to replicate it from the graph above.
* at the end of *Jupyter Notebook*, create a markdown cell and insert the questions:
  `“When do our users usually commit the labs: in the night, morning, afternoon, or evening?”`, the answer is the two most common periods.
* which day has:
  * the most number of commits?
  * and at the same time, the number of commits in the evening is higher than in the afternoon?

## Exercise 03: bar charts

Turn-in directory: `ex_03/`

Files to turn in: `03_bar_charts.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`

What if the average number of commits is different when it is a working day or weekend?
Do what you need to do to create a graph like this:

* analyze only the users and not the admins.
* for each hour, calculate the average number of commits on working days and on weekends use these values for your graph:
  ![6](content/images/6.png)

* the `fontsize=` and the `figsize=` remain the same.
* choose a palette.
* at the end of *Jupyter Notebook*, create a markdown  cell and insert the question:
  `“Is the dynamic different on working days and weekends?”`
  * for the answer include the hour when the number of commits is the largest during working days and the hour when it is the largest during the weekend.

## Exercise 04: histogram

Turn-in directory: `ex_04/`

Files to turn in: `04_histogram.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`, `import matplotlib.pyplot as plt`

In the previous exercise, you had to draw a distribution grouping the values using *Pandas*.
Wouldn’t it be nice if we could draw it in a more automatic way?
Well, we can.
But we have to use another type of visualization – histograms.
This time, we will not use the averages.
We will use the absolute numbers of commits and will compare them during working days and weekends.
Do what you need to do to create a graph like this:

![7](content/images/7.png)

* analyze only the users and not the admins.
* create two lists of values for the histogram input.
* the `figsize=` is still the same, you can choose the `fontsize=` as well as the color palette.
* use a level of transparency for the histogram in front equal to `0.7`.
* at the end of *Jupyter Notebook*, create a markdown cell and insert the question:
  `“Are there hours when the total number of commits was higher on weekends than on working days?”`

## Exercise 05: boxplot

Turn-in directory: `ex_05/`

Files to turn in: `05_boxplot.ipynb`

Allowed functions: `import pandas as pd`, `import matplotlib.pyplot as plt`

Remember how we tried to figure out if the newsfeed affected the behavior of the test and control users?
Last time, we just calculated the average values.
But do we know something about the variances?
What if it changed too?
What if we had some outliers?
To answer those questions it may be handy to draw a boxplot.
Do what you need to do to create a graph like this:

![8](content/images/8.png)

* use the data from the [file](https://drive.google.com/file/d/1B6M7Ku89ViIStXvWU6j7PyDnCTb0McEI/view?usp=sharing) to a *Pandas* dataframe.
* the `figsize=` is still the same, you can choose whatever `fontsize=` you like.
* the color palette should be the same as in the example.
* the `fontsize=` of the title is `16`.
* the width of the box lines is `3`, the width of the median lines is `2`.
* at the end of *Jupyter Notebook*, create a markdown cell and insert the question:
  `“What was the *IQR* of the control group before the newsfeed?”`

## Exercise 06: scatter matrix

Turn-in directory: `ex_06/`

Files to turn in: `06_scatter_matrix.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`, `from pandas.plotting import scatter_matrix`

Remember how we tried to find out if there was a correlation between the number of visits to the `Newsfeed` and the average difference between the first commit and the lab deadline?
The problem is that the correlation coefficient shows whether there is a linear relationship between the two variables.
But what if it is not linear?
How can we see that?
That’s right – by drawing graphs!
Do what you need to do to create a graph like this:

![9](content/images/9.png)

* create a *Pandas* dataframe where each user of the test group has: the average difference, number of pageviews, number of commits.
* do not take `project1` into account for calculations of the average difference and the number of commits.
* take the number of commits from the `checker` table.
* the `figsize=` is still the same, you can choose whatever `fontsize=` you like as well as the color palette.
* the size of the dots should be `200`.
* the width of the lines of the diagonal graphs should be `3`.
* at the end of *Jupyter Notebook*, create a markdown cell and insert the questions:
  * `"Can we say that if a user has a low number of pageviews then they likely have a low number of commits?"`
  * `"Can we say that if a user has a low number of pageviews then they likely have a small average difference between the first commit and the lab deadline?"`
  * `"Can we say that there are many users with a low number of commits and a few with a high number of commits?"`
  * `"Can we say that there are many users with a small average difference and a few with a large average difference?"`

## Exercise 07: heatmap

Turn-in directory: `ex_07/`

Files to turn in: `07_heatmap.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`, `import matplotlib.pyplot as plt`, `from mpl_toolkits.axes_grid1`, `import make_axes_locatable`

Several exercises back, we wanted to see if there are different patterns for users during working days and weekends.
In this exercise, let us find out if there are different patterns for users between different weekdays and between different hours.

* analyze only the users and not the admins.
* use the table `checker` for your query.
* use absolute values of the commits, not the averages.
* sort the dataframes by the total number of commits made by a user.
* choose the color palette for both of the graphs that will need to draw.
  ![10](content/images/10.png)

* at the end of *Jupyter Notebook* create a markdown cell and insert the questions:
  * `"Which user has the most commits on Tue?"`
  * `"Which user has the most commits on Thu?"`
  * `"On which weekday do the users not like making a lot of commits?"`
  * `"Which user at which hour made the largest number of commits?"`

## Exercise 08: *Seaborn*

Turn-in directory: `ex_08/`

Files to turn in: `08_seaborn.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`, `import matplotlib.pyplot as plt`, `import seaborn as sns`

Ok, sometimes in the previous exercises we ignored `project1` in our calculations.
The project was a competition.
It had longer deadlines and much more commits than ordinary labs had.
Let us see the dynamic of commits in this project per user.
This time we will use another library for data visualization in *Python* – *Seaborn*.
In general, it is much easier to create something beautiful in that library.
Do what you need to do to create a graph like this:

![11](content/images/11.png)

* analyze only the users and not the admins.
* take into account only logs from the table `checker` where the `status` is `ready`.
* choose the palette.
* the linewidth should be `3`.
* the background of the graph is `gray`.
* the height should be `10`, and the width should `1.5x` in relation to the height.
* the `fontsize=` of the title should be `30`.
* the `fontsize=` of the axises labels is `15`.
* at the end of *Jupyter Notebook* create a markdown cell and insert the questions:
  * `"Which user was the leader in the number of commits almost all of the time?"`
  * `"Which user was the leader for only a short period of time?"`

## Exercise 09: *Plotly*

Turn-in directory: `ex_09/`

Files to turn in: `09_plotly.ipynb`

Allowed functions: `import pandas as pd`, `import sqlite3`, `import plotly.graph_objects as go`, `import numpy as np`

*Matplotlib* and *Seaborn* are really powerful libraries and you can use them for most of the tasks that you may have related to *DataViz*.
But they do not offer you the functionality of creating interactive charts and animations.
And *Plotly* can help you with that.
In this exercise, you will need to create almost the same graph as in the previous exercise but in an animation.
Do what you need to do to create a graph like this:

![12](content/images/12.png)
