# *Object-oriented programming* (*OOP*)

OOP is a programming paradigm used to structure and organize code as interacting objects.
Classes are templates or blueprints for creating objects.
They define the attributes (variables) and methods (functions) that will be available to the objects of that class.
In Python, classes are defined using the `class` keyword.
Objects are specific instances of classes.
They are created based on classes using a class constructor.
Object initialization is performed using the `__init__` method, which is automatically called after a new object is created. This method sets the initial values of the object's attributes (although technically attributes can be added later as well). When referring to a class constructor in Python, it's usually the `__init__` method that is meant.

*Note on object creation in Python:* The process of creating an object in Python consists of two stages:

1. Creation — performed by the `__new__(cls, ...)` method, which creates and returns a new instance of the class.
2. Initialization — performed by the `__init__(self, ...)` method, which configures the newly created instance.

In 99% of cases, it is sufficient to define only `__init__`, since the standard implementation of `__new__` already creates the instance correctly.
The `__new__` method is only required for special tasks (creating immutable objects, implementing the Singleton pattern, etc.).
Attributes are variables that belong to class objects.
They can be unique to each object (instance) or shared among all objects of a class.
Attributes can be defined inside class methods or in the `__init__` method.
Methods are functions that belong to class objects.
They can perform operations on the object's data or return values.
Methods can be common to all objects of the class or unique to each one.
Dunder methods (also known as special methods or magic methods) are special methods with double underscores at the beginning and end of their names.
There are many of them, and they allow overriding the default behavior of operators and built-in functions for class objects.

For example:

- `__init__` — object initialization method
- `__str__` — used to define the string representation of an object
- `__add__` — defines how the `+` operator works for class instances and so on.

```python
class Circle:
    def __init__(self, radius):
        self.radius = radius

    def __str__(self):
        return f" Circle with radius {self.radius}"

    def __add__(self, other):
        if isinstance(other, Circle):
            return Circle(self.radius + other.radius)

        raise TypeError

circle1 = Circle(5)
circle2 = Circle(3)
circle = circle1 + circle2

print(circle1)  # Output: "Circle with radius 5"
print(circle2)  # Output: "Circle with radius 3"
print(circle)  # Output: "Circle with radius 8"
```

Static methods are methods that are bound to the class rather than its instances.
They are called using the class name, not an instance.
In Python, static methods are declared using the `@staticmethod` decorator.
They do not require access to the instance (`self`) and can be used even if no instances of the class exist.
This is useful when the functionality does not depend on the instance’s state and does not require access to instance attributes.

```python
class MathOperations:
    @staticmethod
    def add(x, y):
        return x + y

    @staticmethod
    def multiply(x, y):
        return x * y

# Calling static methods using the class name
sum_result = MathOperations.add(3, 5)  
product_result = MathOperations.multiply(4, 6)

print(f"Sum: {sum_result}") # Output: Sum: 8  
print(f"Product: {product_result}") # Output: Product: 24
```

## Key Concepts  

### Abstraction

Abstract classes in Python are classes that cannot be instantiated directly.
They are used to define interfaces that other classes must implement.
Such classes can include abstract methods that have no implementation in the abstract class itself but must be implemented in derived subclasses.
This allows the definition of common interfaces with different implementations in each specific subclass.  
To create abstract classes in Python, the abc module (Abstract Base Classes) is used.

```python
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

    @abstractmethod
    def perimeter(self):
        pass

class Square(Shape):
    def __init__(self, side_length):
        self.side_length = side_length

    def area(self):
        return self.side_length ** 2

    def perimeter(self):
        return 4 * self.side_length

class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.14 * self.radius ** 2

    def perimeter(self):
        return 2 * 3.14 * self.radius

# Usage example
square = Square(5)
circle = Circle(3)

print("Square area:", square.area()) # Output: 25
print("Square perimeter:", square.perimeter()) # Output: 20
print("Circle area:", circle.area()) # Output: 28.26
print("Circle perimeter:", circle.perimeter()) # Output: 18.84
```

In the example above, `Shape` is an abstract class with abstract methods `area` and `perimeter`.
The `Square` and `Circle` classes are subclasses that are required to implement both of these methods.
If any of the abstract methods are not implemented in a subclass, attempting to create an instance of such a class will result in a `TypeError`.

### Inheritance

Inheritance allows the creation of new classes based on existing ones.
A subclass inherits the attributes and methods of its parent class and can extend or override them without the need to rewrite the code.
In Python, inheritance is implemented by adding parentheses with the name of the parent class after the class name, as in: `class A(B)`.

### Encapsulation

Encapsulation means that data (variables) and the methods that work with this data are usually grouped inside a class.
This makes it possible to hide implementation details and provide a clear interface for interacting with objects.
This principle is called encapsulation.
In Python, there are three levels of access to class attributes and methods:

### Public attributes and methods

Accessible from anywhere in the program.
Public attributes are usually defined without any special prefixes or suffixes.

### Protected attributes and methods

Accessible only within the class and its subclasses.
Protected attributes are usually defined with a single underscore prefix, e.g., `_protected_attribute`.

### Private attributes and methods

Accessible only within the class and not accessible from the outside.
Private attributes are usually defined with a double underscore prefix, e.g., `__private_attribute`.
It is important to note that Python uses a name mangling mechanism for private attributes and methods.
When a private attribute or method is defined, its name is changed internally by adding a `_ClassName` prefix to the original name.
In other words, Python does not enforce strict protection from accessing protected or private members from outside the class. Therefore, there is a convention known as the "Principle of Least Astonishment," which states that private attributes and methods are meant to indicate their intended use for internal purposes only.

```python
class MyClass:
    def __init__(self):
        self.public_attribute = "This is a public attribute"
        self._protected_attribute = "This is a protected attribute"
        self.__private_attribute = "This is a private attribute"

    def public_method(self):
        return "This is a public method"

    def _protected_method(self):
        return "This is a protected method"

    def __private_method(self):
        return "This is a private method"

obj = MyClass()

print(obj.public_attribute) # Output: "This is a public attribute"
print(obj._protected_attribute) # Output: "This is a protected attribute"
print(obj._MyClass__private_attribute) # Output: "This is a private attribute"

print(obj.public_method()) # Output: "This is a public method"
print(obj._protected_method()) # Output: "This is a protected method"
print(obj._MyClass__private_method()) # Output: "This is a private method"
```

### Polymorphism

Polymorphism allows objects of different classes to share a common interface while behaving differently.
This enables the use of objects from various classes in generic operations. For example, different classes may have a `speak` method, but each class can implement it in its own way.

```python
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        pass

class Dog(Animal):
    def speak(self):
        return f"{self.name} says 'Woof!'"

class Cat(Animal):
    def speak(self):
        return f"{self.name} says 'Meow!'"

dog = Dog("Bobik")
cat = Cat("Murzik")

print(dog.speak()) # Output: "Bobik says 'Woof!'"
print(cat.speak()) # Output: "Murzik says 'Meow!'"
```
