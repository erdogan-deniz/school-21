# Day 01: *Python* bootcamp

Summary: today you will learn about the main functions of the *Python* language.

## Foreword

*Python* is a high-level, interpreted programming language that has a simple
syntax.
In `1980`s, *Guido van Rossum* of the *Dutch National Research Institute* for
*Mathematics and Computer Science* proposed the idea of creating a programming
language.
*Guido* was involved in the development of the *ABC* language for studying
programming.
The *ABC* project failed and *Guido* moved on to programming other projects
involving the *Amoeba* operating system.
In `1989`, the *Amoeba* system lacked a scripting language, so *Guido van*
*Rossum* planned a mini project: to write a programming language based on the
*ABC* developments.
The first prototype consisted of: a simple virtual machine, a parser, a runtime
environment.
*CWI* developers liked the *Python* prototype, many of them got involved right
away: they started using the language for projects and helped refine the code.
In `February 1991`, *Guido* published the source code for *Python* version
`0.9.0` in the group news.
This release had modules borrowed from *Modula-3*.
*Van Rossum* described the module as "one of the main elements in *Python*
programming".
*Python* `1.0` was released in `January 1994`.
The last version released by *Van Rossum* while working at the *Center for
Mathematics and Informatics* was *Python* `1.2`.
On `June 29, 1994`, the forum published an article that addressed the *Python*
community's dependence on *Guido van Rossum's* solutions - the author shared
that companies are afraid of using technologies that are tied to one person.
The article was written by *Michael McLay* of the *US National Institute of*
*Standards and Technology*.
He recruited *Guido* to work with him, this led to the creation of the *Python*
*Software Foundation* in `1995` — a non-profit organization that was to be for
the protection and development of the *Python* language.
This organization got leaders, *Guido van Rossum* was given the title of
*Benevolent Dictator For Life*.
The second version of *Python* appeared in `2000`, the third version in `2008`.
Since late `2020`, the official *Python* community has only supported the third
version.

*Python's main advantages*:

1. Сode readability: *Python* syntax is easy to read and understand.
   It helps to develop programs quickly and simplifies code maintenance.
2. Interpretability: *Python* is an interpreted language, which means that the
   code is executed line by line by an interpreter rather.
   This makes development and testing easier.
3. Multitasking: *Python* supports synchronous and asynchronous programming.
   This allows to efficiently solve tasks, including processing big data,
   creating web applications, solving scientific problems.
4. A large community: *Python* has an developer community, which contributes to
   an extensive library of modules and frameworks.
   This makes *Python* a powerful tool for a variety of tasks.
5. Wide use: *Python* is used in various fields such as web development,
   data analysis and machine learning, task automation, scientific research,
   game creation.
6. Portability: *Python* is a cross-platform language, which allows programs to
   run on different operating systems without changes to the source code.
7. Object-oriented programming: *Python* supports object-oriented programming,
   which makes code easier to organize and more modular.

## Exercise 00: creating a project

For development in the *Python* language, you will need to install the
interpreter.
You can use the *command line* or *integrated development environment* (*IDE*)
to work on project.
A project is a set of files with the extension `.py`, which contain *Python*
code.
They are run with the *Python* command `python3` or imported into file, for
example `main.py`.
A *virtual environment* is used for projects with: libraries, frameworks.
Take a screenshot of project.

## Exercise 01: a scalar product

Calculate the scalar product of two vectors in three dimensional space.
Do not check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Real numbers, coordinates of two vectors on two lines.

*Output*:

- Real number, scalar product of vectors.

*Example*:

Input:
`1.0 2.0 3.0`
`4.0 5.0 6.0`

Output:
`32.0`

## Exercise 02: a palindrome

Determine whether the number is a palindrome or not.
Negative numbers are not palindromes.
Do not use strings.
Do not check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Integer number.

*Output*:

- `True` if a number is a palindrome.
- `False` if a number is not a palindrome.

*Example*:

Input:
`1143411`

Output:
`True`

## Exercise 03: a figures

Process a square matrix of zeros and ones, count the number of "squares" and
"circles" in it.
The figures cannot be beyond the boundaries of the matrix.
There is an space between any figures.
There are no other figures in the matrix.
Identified figures contain more than one unit.
Use the `input.txt` file to get matrix.
Do not check the correctness of the input data.
Use the standard output stream to output data.

*Input*:

- The rows of a square matrix, each containing zeros or units separated by a
  space.

*Output*:

- Two natural numbers separated by a space, the number of "squares" and the
  number of "circles".

*Example*:

Input:
`0 0 0 0 0 0 0 0 1 0`
`0 1 1 1 0 0 0 1 1 1`
`0 1 1 1 0 0 0 0 1 0`
`0 1 1 1 0 0 0 0 0 0`
`0 0 0 0 0 0 0 0 0 0`
`0 1 1 0 0 1 1 0 0 0`
`0 1 1 0 1 1 1 1 0 0`
`0 0 0 0 1 1 1 1 0 0`
`1 1 0 0 0 1 1 0 0 0`
`1 1 0 0 0 0 0 0 0 0`

Output:
`3 2`

## Exercise 04: a *Pascal's triangle*

Print `n` rows of *Pascal's triangle* by the number `n` of rows.
Check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Integer, number of rows.

*Output*:

- Integer numbers, *Pascal's triangle*.

*Example*:

Input:
`5`

Output:
`1`
`1 1`
`1 2 1`
`1 3 3 1`
`1 4 6 4 1`

## Exercise 05: a string to float conversion

Convert a string to a real number.
Do not use `float()`.
Multiply the result by `2`.
Print the result with three digits after the dot.
Check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- A string.

*Output*:

- A real number if the input is correct.
- An error message if the input is incorrect.

*Example*:

Input:
`-14.97`

Output:
`-29.940`

## Exercise 06: a movies

Join two lists of movies sorted by the `year` field.
Use the `movies.json` file to enter data.
The input data is in *.json* format.
Output the joined list in *.json* format.
Check the correctness of the input data.
Use the standard output stream to output data.

*Input*:

- Two sorted lists of movies in *.json* format.

*Output*:

- The joined sorted list in *.json* format if the input is correct.
- An error message if the input is incorrect.

*Example*:

Input:

```json
{
  "list_one": [
    {
      "title": "Titanic",
      "year": 1998
    },
    {
      "title": "Taxi 2",
      "year": 2000
    },
    {
      "title": "Avatar",
      "year": 2009
    }
  ],
  "list_two": [
    {
      "title": "Terminator",
      "year": 1984
    },
    {
      "title": "Home Alone",
      "year": 1993
    },
    {
      "title": "Spider-Man",
      "year": 2002
    }
  ]
}
```

Output:

```json
{
  "list": [
    {
      "title": "Terminator",
      "year": 1984
    },
    {
      "title": "Home Alone",
      "year": 1993
    },
    {
      "title": "Titanic",
      "year": 1998
    },
    {
      "title": "Taxi 2",
      "year": 2000
    },
    {
      "title": "Spider-Man",
      "year": 2002
    },
    {
      "title": "Avatar",
      "year": 2009
    }
  ]
}
```

## Exercise 07: a robot

The field is rectangular and filled with numbers: number of coins.
The robot can move down or to the right one step.
It is initially located in the top left square.
The robot collects coins from each square it walked on.
The task is to collect as many coins as possible on the way to the bottom right
square of the field.
Determine how many coins the robot will collect.
Do not check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Two natural numbers, the number of rows `n` and the number of columns `m` of a
  field.
- `n` rows, each containing `m` non-negative numbers, the number of coins.

*Output*:

- A non-negative integer number, the number of coins the robot will collect.

*Example*:

Input:
`3 4`
`3 0 2 1`
`6 4 8 5`
`3 3 6 0`

Output:
`27`

## Exercise 08: a different numbers

Count the number of different numbers.
Do not check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Natural number, the number of numbers `n`.
- `n` lines, each containing an integer number.

*Output*:

- A natural number, the number of different numbers.

*Example*:

Input:
`10`
`5`
`3`
`7`
`3`
`6`
`3`
`5`
`2`
`9`
`4`

Output:
`7`

## Exercise 09: the derivative at a point

Calculate the derivative of a polynomial at a point.
Print the result with three digits after the dot.
Do not check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- The natural and real numbers: the highest degree of the polynomial `n`, the
  point at which need to find the derivative.
- `n` lines, every line contains a real number, the coefficient at `x`.

*Output*:

- The real number, the derivative of a polynomial at a point.

*Example*:

Input:
`2 3.0`
`5`
`1.2`
`-3`

Output:
`31.200`

## Exercise 10: a machines

The machine has: year of manufacture, cost, running time.
Print two machines cost that will spend a certain time, the cost should be
minimal and the year of manufacture should be the same.
Check the correctness of the input data.
Use standard input stream and standard output stream.

*Input*:

- Two natural numbers separated by a space: number `num_of_machines` of
  machines, certain running time.
- `num_of_machines` lines, each containing three natural numbers separated by a
  space: manufacture year, cost, running time of the machine.

*Output*:

- A number if the input is correct.
- An error message if the input is incorrect.

*Example*:

Input:
`5 48`
`2023 100 14`
`2020 18 347`
`2023 10000000 34`
`2023 1000 34`
`2022 10 34`

Output:
`1100`
