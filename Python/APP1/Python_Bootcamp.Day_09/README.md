# Day 09 - Python Bootcamp

## Fast and Curious

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Still Counts](#exercise-00-still-counts)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Split-Second](#exercise-01-split-second)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Autopilot](#exercise-02-autopilot)

## Chapter I
### General rules

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

## Chapter II
### Rules of the day

- You should turn in `*.py`, `*.c`, `*.pyx` and `requirements.txt` (if using external dependencies) files for this task.

## Chapter III
### Intro

 "Oh come on, Dom, you're racing for years already, you're telling be you've never
 configured an [ECU](https://en.wikipedia.org/wiki/Engine_control_unit)?"
 
 It was obvious that Letty wasn't angry, just playful.
 
 "Aren't those always proprietary and sealed?"
 
 "Not really, if you have the right equipment," she poked his forehead with a dirty 
 mechanic glove. "Especially here."
 
 "Okay then. So, it should react to a bunch of sensors and do it really fast."
 
 Toretto pulled a laptop from the table and put it on a toolbox in front of him. He wanted
 to connect to the unit, but Letty raised her hand.
 
 "I know how you usually like to dig too deep. Let's start with something simple."

## Chapter IV
### Exercise 00: Still Counts

Letty pulled up a chair and sat astride it.

 "You know the main issue with Python? It's flexible, but slow. This is not an issue unless
 you want to have a fast thing which is flexible to control."
 
Dominic scratched his head for a second, then nodded.

 "We have to fallback to C in these cases, right?"

 "For example. I know you know basic C already. Anyway, I doubt it will be a problem
 for you to write a function to, say, sum up two numbers?"
 
-----

You have to write a simple calculator module for Python (using Python C API) with four functions:

- `add(a, b)`
- `sub(a, b)`
- `mul(a, b)`
- `div(a, b)`

This module should consist of two files - 'calculator.c' and 'setup.py' for building it.
In regular part of EX00 let's assume the numbers are integers:

```python
>>> import calculator
>>> calculator.add(14.5, 21.87)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: integer argument expected, got float
>>> calculator.add(14, 21)
35
>>> calculator.sub(14, 21)
-7
>>> calculator.mul(14, 21)
294
>>> calculator.div(14, 7)
2
```

Also, your code should handle zero division errors properly, raising a built-in Python exception
from the C code:

```python
>>> import calculator
>>> calculator.by(14, 0)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
ZeroDivisionError: Cannot divide by zero
```

The module should only include two files mentioned above and be installable using
`python setup.py install`

BONUS: upgrade the code of your calculator so it can handle both int and float values for both 
operands.

## Chapter V
### Exercise 01: Split-Second

The engine roared a couple of times outside and in a couple of minutes a garage door opened.

 "Brian, come on it!" Toretto waved invitingly. "Have you ever programmed any ECUs?"
 
Letty giggled, but tried to hide that. 
 
 "Hey Dominic! Well, not really, but I know what's the main challenge."
 
 "Making it go as fast as possible? Just like with cars in general?"
 
 "Actually, it's making *SURE* that it goes faster than before. Do you know how computers
 measure time?"
 
Dominic raised an eyebrow, but Letty immediately responded: 
 
 "Every computer has at least two types of clocks - one stores current time and one 
 measures periods of it, so a machine can compare them."
 
 "Exactly!" Brian smiled. "So when it comes to split-seconds there is a physical crystal 
 on a board which vibrates on a certain frequency. To compare two time deltas you can just look
 at two numbers which are guaranteed to strictly increase tick by tick while time passes.
 
 "Oh, I remember it now," Dominic stood up to shake Brian's hand. "That's why digital 
 car parts have monotonic clocks."
 
-----

You need to use a built-in `ctypes` library in Python to implement an interface to a monotonic 
clock in your operating system. Windows, Linux and MacOS have the function as a part of a standard
library. Python [also has it now](https://peps.python.org/pep-0418/#time-monotonic), but you
should write your own version from scratch.

It should be a function `monotonic()` in a file called `monotonic.py` and a returned value should
be in seconds (some OSes also support nanoseconds). 

## Chapter VI
### Exercise 02: Autopilot

The preparations for the heist were almost completed, roles assigned, and all of the equipment 
upgraded. One of the advanced prototypes included machine learning powered steering control 
unit. Its main purpose was to save driver's life at all costs during possible collisions and 
dangerous situations, analyzing the surroundings with cameras and depth sensors.

Dominic pulled Brian aside for a couple of minutes before the briefing.

 "You know some people on this team are a family to me. Including you. We've talked a lot
 about computers and control units this morning - can you once again tell me that this device will
 do its best to keep everyone safe? Is it fast enough?"
 
 "You know this is a top notch prototype created by some very clever people."
 
 "I know. I just needed a confirmation. Do you have any idea how it actually works?"
 
Brian smiled and then just whispered one phrase trying to sound as spooky as possible:

 "It multiplies matrices!"
 
-----

This time you need to use a third way to speed up computation in Python, which is [Cython](https://cython.org/).
We don't go into Data Science, but [multiplying matrices](https://en.wikipedia.org/wiki/Matrix_multiplication) is a pretty easy and
straightforward procedure.

The sample simplified Python code for it may look somewhat similar to this:

```python
from itertools import tee 

def mul(a, b):
    b_iter = tee(zip(*b), len(a))
    return [
        [
            sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) 
            for col_b in b_iter[i]
        ] for i, row_a in enumerate(a)
    ]
```

You have to write your own function `mul()` in Cython (filename is `multiply.pyx`) and (as in EX00) 
implement a proper `setup.py` file to make a Python package called 'matrix':

```python
from matrix import mul

x = [[1,2,3],[4,5,6],[7,8,9],[10,11,12]]
y = [[1,2],[1,2],[3,4]]

print(mul(x, y))
"""[[12, 18], [27, 42], [42, 66], [57, 90]]"""
```

For simplicity, let's say your code should only work with integers and matrices are no larger than
100x100. Also, don't use built-in implementation from [Numpy](https://numpy.org/) for this task,
even though in production code that would be probably one of the preferred ways.

BONUS: write a performance test in file `test_mul_perf.py` comparing basic pure Python
implementation with your Cython one. It should be a lot faster.

**Please leave your feedback [here](https://forms.gle/pAiwZa3HLZJcLSpC9)**
