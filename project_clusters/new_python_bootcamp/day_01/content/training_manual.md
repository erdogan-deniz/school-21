# Control structures

Control structures (sequential, branching, repetition) are the basic building
blocks for creating programs.
Using them allows developers to efficiently manage the flow of program execution
and create complex and functional applications.

## Sequence

This is a basic control structure in which instructions are executed
sequentially, one after the other, from top to bottom.

```python
print("Step 1", )
print("Step 2", )
print("Step 3", )
```

## Branching

This structure allows certain instructions to be executed only under certain
conditions.
*Python* uses the `if` statement, as well as `elif` (else if) and `else`.

```python
x: int = 10

if x > 0:
    print("x positive", )
elif x == 0:
    print("x equal 0", )
else:
    print("x negative", )
```

With *Python* `3.10`, a new structure was introduced to control the flow of
program execution - `match case`.
It is designed for more convenient and readable condition handling when you want
to compare the value of a variable with several possible values at once.

```python
def check_number(x: int) -> None:
    """
    ...
    """

    match x:
        case 0:
            print("This is zero", )
        case 1 | 2:
            print("This is one or two", )
        case 3 | 4 | 5:
            print("This is three, four, five", )
        case _:
            print("Other value", )


check_number(3, )
```

In the above example, `match case` checks the value of the variable `x` against
various conditions.
The `|` is used to combine multiple values into a single `case`.
The `_` is a wildcard and corresponds to any value.
This structure makes the code clearer and avoids bulky `if-elif-else` chains.
`match case` improves code readability and maintainability.

## Repetition

These structures allow the same block of code to be executed multiple times.
There are two basic types of loops in *Python*: `for` and `while`.

### For

The `for` loop is used to iterate through a sequence and execute specific
instructions for each element in the sequence.

```python
fruits: list[str] = ["apple", "banana", "pear", ]

for fruit in fruits:
    print(fruit, )

for idx in range(5, ):
    print(idx, )
```

### While

The `while` loop is executed as long as the condition is `True`.
It is appropriate when the number of iterations is not known in advance.

```python
count: int = 0

while count < 5:
    print(count, )

    count += 1
```

## Program entry point, program structure

"Program entry point" refers to the place where program execution begins.
In most cases, the entry point is an executable script containing the code that
will be executed when the program is run.
Such a script usually contains a function named `main()`, and this function is
considered the entry point.

An example of a simple *Python* script:

```python
def main() -> None:
    """
    ...
    """

    print("Hello, world!", )


if __name__ == "__main__":
    main()
```

In this example, the `main()` function represents the basic logic of the
program.
The condition if `if __name__ == "__main__":` is then used, to check if the
script is executed directly.
If the script is executed directly, the `main()` function is called.
This structure allows you to easily use code from other programs by importing it
as a module, while avoiding executing the underlying logic if the script is used
as a module.
*Python* program structure can also include variable declarations, function
definitions, conditional statements, loops, other elements, depending on the
complexity of the program.
For example, the structure of a program might look like this:

```python
from module2 import function2

variable1: int = 42
variable2: str = "Example"


def my_function() -> None:
    """
    ...
    """

    print("This is my finction", )


if variable1 > 0:
    my_function()
else:
    print("Variable less than or equal to zero", )

module1.function1()
function2()
```

The general idea is to organize the code so that it is readable, easily
maintainable, and can be used effectively both in the script itself and in other
programs via import as a module.

## Program compilation/interpretation

*Python* is an interpreted programming language, which means that *Python* code
is not compiled into machine code before execution, as is done, for example, in
*C++* or *Java* programming languages.
Instead, *Python* uses a special program called an interpreter to read and
execute code directly.
When you run a *Python* program, the interpreter reads your code line by line
and translates it into machine commands that the computer can execute.
The benefits of interpretation include faster development by not having to
compile before each testing of code changes.
However, interpretation can also have its disadvantages, such as lower
performance in some cases due to the extra time required to interpret code at
runtime.
In addition, interpretation provides more flexibility, allowing code to run on
different platforms without the need to recompile.
This makes *Python* convenient for writing portable software that can run on
different operating systems without changes to the source code.

## Simple data types

The *Python* language has a few simple data types: numbers, strings, Boolean
values.

## Numbers

In *Python*, you can work with integers and floating point numbers.
Numbers are used to perform mathematical operations and store quantitative
information.

```python
a: int = 15
b: float = 4.2
```

## Strings

Strings are a sequence of numbers characters enclosed in quotes.
They are used to store textual information and can be changeable or
non-changeable.

```python
my_string: str = "Hello, world!"
another_string: str = "It's a different string."
multiline_string: str = """It's
a multiline
string."""
```

Strings can be concatenated - `my_string + another_string`, and you can access
the characters of a string by indices - `my_string[0]`.

## String formatting

String formatting allows you to insert variable values at specific places in a
string or create strings with a specific format, making code more readable and
flexible.

- `Format()` method

```python
name: str = "Alice"
age: int = 30
sentence: str = "My name is {}, and I am {} years old.".format(name, age, )
print(sentence, )  # Output: My name is Alice, and I am 30 years old.
```

- `f-strings`

```python
name: str = "Bob"
age: int = 25
sentence: = f"My name is {name}, and I am {age} years old."
print(sentence, )  # Output: My name is Bob, and I am 25 years old.
```

## Basic methods for working with strings

- `len()`: Returns the length of the string, i.e. the number of characters in
  the string.

```python
my_string: str = "Example string"
length: int = len(my_string, )
print(length, )  # Output: 14
```

- `lower()` and `upper()`: Convert all characters in a string to lower or upper
  case.

```python
my_string: str = "Example String"
lower_case: str = my_string.lower()
upper_case: str = my_string.upper()
print(lower_case, )  # Output: "example string"
print(upper_case, )  # Output: "EXAMPLE STRING"
```

- `strip()`: emoves whitespace characters at the beginning and end of a string.

```python
my_string: str = "   Spaces at the beginning and end   "
stripped_string: list = my_string.strip()
print(stripped_string, )  # Output: "Spaces at the beginning and end"
```

- `replace()`: Replaces a substring with another substring.

```python
my_string: str = "Character replacement"
new_string: str = my_string.replace("а", "о", )
print(new_string, )  # Output: "Chorocter replocement"
```

- `find()` and `index()`: Search for a substring in the string and return the
  index of the first occurrence.
  `find()` returns `-1` if no substring is found, and `index()` raises an
  exception.

```python
my_string: str = "Substring search"
index1: str = my_string.find("substring", )
index2: str = my_string.index("substring", )
print(index1, )  # Output: 6
print(index2, )  # Output: 6
```

- `split()`: Splits a string into substrings by the specified delimiter and
  returns a list.

```python
my_string: str = "Splitting a string into words"
words: list = my_string.split()
print(words, )  # Output: ['Splitting', 'a', 'string', 'into', 'words']
```

- `join()`: Combines elements of a string list into a single string using the
  specified delimiter.

```python
words: list[str] = ["Splitting", "a", "string", "into", "words", ]
my_string: str = ' '.join(words, )
print(my_string, )  # Output: "Splitting a string into words"
```

## Boolean values

Boolean values are logical values `True` and `False`.
They are used to perform logical operations and make decisions in the program.

### Basic Boolean operations

- Conjunction (AND)

Returns `True` if both operands are `True`.
Otherwise, returns `False`.

```python
x: bool = True
y: bool = False

result: bool = x and y
print(result, )  # Output: False
```

- Disjunction (OR)

Returns `True` if at least one of the operands is `True`.
If both operands are `False`, returns `False`.

```python
x: bool = True
y: bool = False

result: bool = x or y
print(result, )  # Output: True
```

- Negation (NOT)

Inverts the boolean value of the operand.
If an operand is `True`, then not will make it `False`, and vice versa.

```python
x: bool = True

result: bool = not x
print(result, )  # Output: False
```

These operations can be combined to create more complex logical expressions.

```python
a: bool = True
b: bool = False
c: bool = True

result: bool = (a and b) or (not c)
print(result, )  # Output: False
```

Boolean values are also often used in conditional statements to make decisions
depending on the fulfillment of certain conditions.

```python
x: int = 10

if x > 5 and x < 15:
    print("x ranges from 6 to 14.", )
else:
    print("x is not ranged from 6 to 14.", )
```

## Composite data types

In *Python*, composite data types provide the ability to store and manage large
amounts of information.
You can group related data into one variable and make the code more organized
and easy to work with.

## A list

One of the most popular composite data types in *Python* is the `list`.
The `list` is an ordered collection of items that can contain objects of
different data types.
You can add, delete, and modify list items, as well as perform various
operations such as sorting and searching.

### List creation

You can create lists using square brackets or the function `list()`.

```python
my_list = [1, 2, 3]
another_list = list((4, 5, 6))  # any iterated object can be passed to the list() function: list, tuple, map, str, etc.
```

### Indexing and slicing

List items can be retrieved by index or by performing slices. Indexing starts at 0.

```python
my_list = [1, 2, 3, 4, 5]
print(my_list[0])  # Output: 1
print(my_list[1:3])  # Output: (2, 3)
```

### The length of a list

You can find out the length of a list using the `len()` function.

```python
my_tuple = (1, 2, 3)
print(len(my_tuple))  # Output: 3
```

### Concatenation and repetition

Lists can be joined using the `+` operator and repeated using the `*` operator.

```python
list1 = [1, 2, 3]
list2 = [4, 5, 6]
concatenated_list = list1 + list2  # Output: [1, 2, 3, 4, 5, 6]
repeated_list = list1 * 3  # Output: [1, 2, 3, 1, 2, 3, 1, 2, 3]
```

### Basic methods for working with lists

#### append()

Adds an item to the end of a list.

```python
my_list = [1, 2, 3]
my_list.append(4)
# Result: [1, 2, 3, 4]
```

#### extend()

Expands a list by adding items of another list to the end.

```python
my_list = [1, 2, 3]
another_list = [4, 5, 6]
my_list.extend(another_list)
# Result: [1, 2, 3, 4, 5, 6]
```

#### insert()

Insert an item at the specified position in a list.

```python
my_list = [1, 2, 3]
my_list.insert(1, 5)  # Insert 5 to position 1
# Result: [1, 5, 2, 3]
```

#### remove()

Removes the first occurrence of an item from the list.

```python
my_list = [1, 2, 3, 2]
my_list.remove(2)
# Result: [1, 3, 2]
```

#### pop()

Deletes an item by index and returns its value. If no index is specified, the last item is deleted.

```python
my_list = [1, 2, 3]
value = my_list.pop(1)  # Delete the item with 1 (2) index and store its value in the value variable.
# Result my_list: [1, 3]
# Result value: 2
```

#### index()

Returns the index of the first occurrence of the specified item in the list.

```python
my_list = [1, 2, 3, 2]
index = my_list.index(2)
# Result: index = 1
```

#### count()

Returns the number of occurrences of the specified item in the list.

```python
my_list = [1, 2, 3, 2]
count = my_list.count(2)
# Result: count = 2
```

#### sort()

Sorts the list in ascending order (or by specific criteria, if specified).

```python
my_list = [3, 1, 4, 2]
my_list.sort()
# Result: [1, 2, 3, 4]
```

## Tuples

Another composite data type `tuple`.
A `tuple` is similar to a `list`, but it is unchangeable, meaning that its items
cannot be changed after creation.
Tuples are often used to represent unchangeable data sets, such as point
coordinates or date and time.

### Tuples creation

You can create tuples using round brackets or the function `tuple()`.

```python
my_tuple: tuple = (1, 2, 3, )
another_tuple: tuple = tuple([4, 5, 6, ], )
```

### Indexing and slicings

As in lists, tuple items can be retrieved by index or by performing slicing.
Indexing starts at `0`.

```python
my_tuple: tuple = (1, 2, 3, 4, 5, )
print(my_tuple[0], )  # Output: 1
print(my_tuple[1: 3], )  # Output: (2, 3)
```

### Tuple length

You can find out the length of a tuple using the `len()` function.

```python
my_tuple: tuple = (1, 2, 3, )
print(len(my_tuple, ), )  # Output: 3
```

### Concatenation and repetitions

Tuples can be joined using the `+` operator and repeated using the `*` operator.

```python
tuple1: tuple = (1, 2, 3, )
tuple2: tuple = (4, 5, 6, )
concatenated_tuple: tuple = tuple1 + tuple2  # Output: (1, 2, 3, 4, 5, 6)
repeated_tuple: tuple = tuple1 * 3  # Output: (1, 2, 3, 1, 2, 3, 1, 2, 3)
```

Tuples have all the methods of lists that don't modify them.
For example, `count()`, `find()`, `index()` and others.

## Dictionaries

A `dictionary` is another powerful composite data type in *Python*.
It is a collection of key-value pairs.
Dictionaries allow you to quickly find values by key and manipulate data in a
more structured format.

### Dictionary creation

You can create dictionaries using curly brackets or the function `dict()`.
An empty dictionary can only be created using the second method, since empty
curly brackets create an empty set.

```python
my_dict: dict[str, int] = {"apple": 2, "banana": 4, "orange": 6, }
```

### Adding an item

```python
my_dict["grape"] = 3
```

### Retrieving value by key

```python
print(my_dict["apple"], )  # Output: 2
```

### Checking for a key in the dictionary

```python
print("pear" in my_dict, )  # Output: False
```

### Deleting an item by key

```python
del my_dict["banana"]
```

### Retrieving all keys or dictionary values

```python
keys: list[str] = my_dict.keys()
values: list[int] = my_dict.values()
```

### Retrieving all key-value pairs of the dictionary

```python
items: list[str, int] = my_dict.items()
```

### Updating a dictionary with another dictionary

```python
new_dict: dict[str, int] = {"kiwi": 5, "grapefruit": 8, }
my_dict.update(new_dict, )
```

### Enumeration of dictionary elements

```python
for key, value in my_dict.items():
    print(key, value, )
```

### Clearing the dictionary

```python
my_dict.clear()
```

## Sets

There are sets in *Python*, which are unordered collections of unique items.
Sets are useful for removing duplicates and performing operations on sets, such
as union, intersection, difference.

### Sets creation

You can create sets using curly brackets or the function `set()`.

```python
my_set: set[int] = {1, 2, 3, 4, 5, }  # Creating a set using curly brackets 
```

### Adding an item in a set

```python
my_set.add(6, )  # Adding item 6 to the set
```

### Removing an item from a set

```python
my_set.remove(3, )  # Removing item 3 from the set
```

### Checking the availability of an item in a set

```python
if 4 in my_set:
    print("Item 4 is in the set", )
```

### Union of two sets

```python
my_set2: set[int] = {5, 6, 7, 8, 9, }
union_set: set[int] = my_set.union(my_set2, )  # Set union
```

### Intersection of two sets

```python
intersection_set: set = my_set.intersection(my_set2, )  # Set intersection
```

### Difference of two sets

```python
difference_set: set = my_set.difference(my_set2, )  # Set difference
```

### Subset check

```python
if my_set.issubset(my_set2, ):
    print("The set my_set is a subset of my_set2", )
```

### Disjoint sets check

```python
if my_set.isdisjoint(my_set2, ):
    print("The sets my_set and my_set2 have no items in common", )
```

## Input/Output

Standard *I/O* streams are usually denoted as *stdin* and *stdout*.
These streams are abstractions through which the program interacts with the
outside world, reading data from the console and writing execution results to
the console.

## *Stdin*

*Stdin* is the stream where the program receives input from the user or from
another source.
In *Python*, data from *stdin* can be read using the `input()` function.
It waits for input from the user and returns it as a string.

```python
name: str = input("Enter your name: ", ) 
```

## *Stdout*

*Stdout* is the stream where the program sends the results of its work.
In *Python*, the `print()` function outputs data.
It takes one or more arguments and outputs them, adding a sep delimiter after
each argument, and an end at the end.

```python
print("This message will be output to the stdout.", ) 
```

```python
input_number: str = input("Enter a number: ", )

try:
    input_number: float = float(input_number, )
    result: float = input_number * 2

    print("Result of multiplication by 2:", result, )
except ValueError:
    print("Error: Enter the valid number.", )
```

## Memory management, garbage collector

*Python* automatically manages memory and provides a high-level interface for
working with objects, without requiring the programmer to explicitly manage
memory as some other programming languages do.
*Garbage collector* is a is a mechanism that automatically frees memory occupied
by objects that are no longer used in the program.
The garbage collector analyzes objects that are no longer referenced and frees
the memory they occupied.
This helps avoid memory leaks and ensures efficient resource utilization.
In *Python*, there is a garbage collector called a "reference counter".
It tracks the number of references to each object.
When the number of references to an object becomes zero, the garbage collector
automatically frees the memory occupied by that object.
However, *Python* also offers other garbage collection mechanisms such as mark
and sweep and generational mechanism.
These mechanisms are much more complex, but they allow for more efficient memory
management, which can sometimes be useful.

## Complex data structures

*Python* allows you to create complex data structures by inserting compound data
structures into each other, obtaining, for example, lists of lists, lists of
tuples, dictionaries of dictionaries.

```python
matrix: list[list[int]] = [
    [1, 2, 3, ],
    [4, 5, 6, ],
    [7, 8, 9, ],
]
users: dict[str, object] = {
    "user1": {
        "name": "Alice",
        "age": 25,
        "email": "alice@example.com",
    },
    "user2": {
        "name": "Bob",
        "age": 30,
        "email": "bob@example.com",
    },
}
```

The `typing` module in *Python* provides tools to support annotation of data
types.
It allows you to declare complex data types such as lists of certain objects,
dictionaries with certain keys and values, tuples of different types.
This helps improve the readability of the code and makes it easier to maintain.
*Python* also offers other complex data structures, such as, `collections`.
They provide different ways of storing and arranging data depending on your
specific needs.
It is important to choose data structures depending on the task, considering
data access requirements, speed of operations and other characteristics.
*Python* provides a wide range of tools for working with data, making it a
convenient and flexible programming language.

## Exception handling

Exception handling is a mechanism for handling errors and unusual situations in
a program.
When an error occurs during code execution, *Python* creates an exception object
and tries to find the appropriate exception handling block.

```python
try:
    x: int = int(input("Enter a number: ", ), )
    result: int = 10 / x
except ValueError as e:
    print(f"Error: Not a number. {e}.", )
except ZeroDivisionError:
    print("Error: Division by zero.", )
else:
    print(f"Result: {result}", )
finally:
    print("End of program.", )
```

## Main elements

- `try`: This block holds the code where an exception can occur.
- `except`: Here you specify the type of exception you want to catch.
  If an exception of this type occurs, control is passed to the appropriate
  except block.
- `as e`: The variable `e` is used to store information about the exception,
  which provides additional information about the error that occurred.
- `else`: This block is executed if no exceptions occurred in the `try` block.
- `finally`: The code in this block is always executed, regardless of whether
  an exception has occurred or not.
  This is where code is usually placed for finalizing actions such as closing
  files or network connections.

## Functions

A function is a block of code that has a name, accepts arguments, performs a
specific task, and possibly returns a result.
Functions allow you to organize your code, make it more readable, and avoid
duplication.

```python
def greeting(name: str) -> Noe:
    """
    A function that greets by name.
    """

    print(f"Hello, {name}!", )

greeting("Anna", )
```

Recursion is a concept where a function calls itself.
Recursion is usually used to solve problems which can be broken down into
smaller subtasks.
For example, we can recursively calculate the factorial of some number `n`.
The factorial of a number `n` is the product of all integers from `1` to `n`.

```python
def factorial(n) -> float:
    """
    Recursive function for calculating the factorial of a number.
    """

    if (n == 0) or (n == 1):
        return 1
    else:
        return n * factorial(n - 1, )


result: int = factorial(5, )

print(result, )
```

When we use recursion, it is important to provide a base case, to avoid infinite
function calls.
It's also important to keep in mind that the depth of recursion in *Python* is
limited.
This limit can be changed using the `setrecursionlimit()` function from the
`sys` standard library, but this is only done in extreme cases, as it is
completely unsafe, and use iterative algorithms whenever possible.
