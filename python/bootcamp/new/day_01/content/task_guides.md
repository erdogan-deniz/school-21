# Methodological guidelines for tasks

## Scalar product

The scalar product is a mathematical operation applied to two vectors in
three-dimensional space (or more) and returns a scalar quantity.
For two vectors: `a = [a1, a2, ..., an, ]` and `b = [b1, b2, ..., bn, ]`, scalar
product is calculated as: `a * b = a1 * b1 + a2 * b2 + ... + an * bn`.
This is the sum of the products of the corresponding components of the vectors.

## Palindrome

A palindrome is a number that reads from left to right and right to left
equally.
You could cast the number to a string and use indices to get the digits, but it
is more efficient to generate a list of digits using integer division operations
in the loop.

## Figures

Write an algorithm that, in the process of traversing the matrix by rows or
columns, for any unit, will start a recursive traversal of all units adjacent to
it.
The encountered units must be replaced by zeros in order to count each one only
once.
There are ways to determine whether a figure is a circle or a square.
One option is to count the number of units during the traversal, save the index
of the leftmost, rightmost, bottom and top units encountered, you can compare
the expected area of the square with the number of units found.

## Pascal's triangle

Pascal's triangle is a number triangle in which each number is equal to the sum
of the two numbers above it.

```python
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
```

## String to number conversion

To convert a string into a real number, write an algorithm that will process the
input string character by character and gather all numbers.
Then use it to get the number itself.
Store in a boolean variable whether the number is positive, a list - the digits
of the final number.
Record the number of digits after the dot in a separate variable, then
reconstruct the number by multiplying each digit by `10` to the desired degree,
then divide by `10` to the number of digits after the dot and multiply by `-1`
if a negative number was entered.

## Movies

Work with the *.json* format using the `json` module, which has the `loads()`
function to get information from the *json* string as a `dict` dictionary, the
`dumps()` function converts the `dict` dictionary into a *json* string.
If a string that does not match the *json* format, a `JSONDecodeError` exception
will be generated.
Catch this exception.
The algorithm to join two sorted lists into a single sorted list must go through
the data once.
If you concatenate two lists and then sort them, the correct list will be, but
algorithm is not the most efficient.

## A robot

The robot can go either down or to the right from each square of the field, the
number of possible trajectories from start to finish is large.
An algorithm that tries all possible robot trajectories to find the most
successful one will be slow, it is not recommended for use.
Use different algorithm of dynamic programming.
The dynamic programming method is used to optimize problems that can be broken
down into smaller subtasks.
The solutions of subtasks can be saved and used to solve the task.
The robot can enter any square only from the top or from the left, choose the
most advantageous of these two options.
This the small subtask, which is solved by simply choosing between the two
options.
Starting from the top left square, be sure for each square following it on the
right and below that the robot has already been able to get into it in the most
convenient way.
We solve the same minor subtask for each subsequent square.
Reaching the bottom right corner of the field, we will get the largest number of
coins, which could be collected in the best case.
The task is solved.

## Different numbers

To count the amount of different numbers entered, you have to save them to
determine whether a number has been encountered yet.
Using a list is not the most efficient way, because you have to check if a
number in the list, this operation going through all the items in the list.
But use a set.
The operation of checking a number belongs to a set is faster.
An alternative is to use a dictionary.
The operation is fast, but it requires a more memory.

## The derivative at a point

The derivative of a polynomial is calculated as the sum of the derivatives of
each of terms.
The derivative of `x` of the polynomial `5 * x**2 + 1.2 * x - 3` will be the sum
of the derivatives of `5 * x**2`, `1.2 * x` and `-3`.
The derivative of each summand of the `a * x**n` the formula
`a * n * x**(n - 1)`.
The derivative of the constant is zero.
For the polynomial get the derivative `10 * x + 1.2`.
Calculate the derivative of the polynomial at a point by substituting the given
value of `x` into the expression.
The derivative at the point `3.0` would be `10 * 3 + 1.2 = 31.2`.
The algorithm for calculating the derivative can find and accumulate the total
sum of the derivative summands.

## Machines

Use `dict` dictionaries to divide machines by year of manufacture.
Store information about machines in the dictionary.
If the key is the machine's operating time, you can check if there is machine in
the dictionary that has the required time in combination with the data.
To minimize the cost, we leave the minimum cost of the machine for each time of
operation in such a dictionary, then the sum will be minimal in the end.
For each year in the dictionary we get a different answer and choose the minimum
one.
