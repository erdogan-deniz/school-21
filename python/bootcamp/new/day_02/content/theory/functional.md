# Functional Paradigm

The functional paradigm in programming is an approach where programs are built around functions.
Instead of a sequence of changing object states, the functional paradigm focuses on defining and applying functions that transform data without modifying the original values.
In Python, the functional paradigm is supported through concepts such as higher-order functions, anonymous functions (lambda functions), decorators, closures, and recursion.
These features enable the creation of more flexible and modular programs.

## **Higher-Order Functions**

Higher-order functions are functions that can take other functions as arguments or return functions as results.

```python
def apply_operation(x, y, operation):
    return operation(x, y)


def add(x, y):
    return x + y


def multiply(x, y):
    return x * y


result = apply_operation(3, 4, add)
print(result)  # Output: 7

result = apply_operation(3, 4, multiply)
print(result)  # Output: 12
```

## **Decorators**

Decorators are functions that take another function as an argument and return a new function, usually wrapped around the original one.
Decorators allow you to add functionality to existing functions without modifying their code.

```python
def uppercase_decorator(func):
    def wrapper():
        result = func()

        return result.upper()

    return wrapper


@uppercase_decorator
def say_hello():
    return "hello"


print(say_hello())  # Output: HELLO
```

In this example, we have a function `uppercase_decorator` that takes another function `func` as an argument and returns a wrapped function `wrapper`.
Inside wrapper, `func` is called, and the result is converted to uppercase before being returned.
Then, using the decorator syntax with the `@` symbol, we apply `uppercase_decorator` to the `say_hello` function.
Now, when `say_hello()` is called, the original function is wrapped by the decorator, and its result will be transformed to uppercase.
Decorators can be useful for various tasks such as logging, authentication checks, caching, and much more.

## **Anonymous Functions (Lambda Functions)**

Anonymous or lambda functions are short functions that can be defined in a single line.
They are useful when you need a small function for short-term use.

```python
add = lambda x, y: x + y
result = add(3, 4)
print(result)  # Output: 7
```

## **Closures**

Closures are functions that remember the values from their enclosing scope, even if that scope has finished executing.
In the example, `outer_function` is called, which defines an `inner_function` inside it.  
Normally, inner functions are not accessible outside the outer function.
However, in this case, the inner function can still be accessed through the result of the outer function, even after it has completed.
This technique is called a closure.

```python
def outer_function(x):
    def inner_function(y):
        return x + y

    return inner_function


closure = outer_function(10)
result = closure(5)

print(result)  # Output: 15
```

## **The map() function**

The `map()` function applies a specified function to each element of a sequence (e.g., a list) and returns a new iterable object with the results.

```python
numbers = [1, 2, 3, 4, 5]
squared = map(lambda x: x ** 2, numbers)

print(list(squared))  # Output: [1, 4, 9, 16, 25]
```

## **The filter() function**  

The `filter()` function is used to filter elements of a sequence using a
predicate.

```python
numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9]
even_numbers = filter(lambda x: x % 2 == 0, numbers)

print(list(even_numbers))  # Output: [2, 4, 6, 8]
```
