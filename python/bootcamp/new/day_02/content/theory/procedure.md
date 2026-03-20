# Procedural Programming

The procedural approach is a way of organizing a program by breaking tasks down into smaller procedures or functions.
Each function performs a specific task and can be called from other parts of the program.
Instead of writing all code in one place, functions and/or procedures are created to implement specific parts of the program logic.
Procedural programming helps simplify code and make it more readable and modular.

```python
def addition(a, b):
    result = a + b

    return result

output = addition(2, 3)

print(output) # Outputs: 5
```

> **A procedure** is a set of instructions that performs a specific task.
It can accept arguments and modify the program state, but unlike a function, it does not return a value.
Procedures are typically used to perform actions such as printing to the screen or modifying variable values.
