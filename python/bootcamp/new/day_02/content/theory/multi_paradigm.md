# Multiparadigm Approach

The multiparadigm approach in programming involves using several programming paradigms simultaneously, depending on the specific task.
This approach makes Python a flexible and versatile programming language, suitable for a wide range of tasks—from simple scripts to complex projects.
Developers can choose the paradigm that best fits the specific requirements and nature of the problem.

```python
# Object-Oriented Approach
class NumberFinder:
    def __init__(self, count: int):
        self.count = count

    def even_numbers(self):
        return [i for i in range(self.count) if i % 2 == 0]
    

# Procedural Approach
def even_numbers(count: int):
    return [i for i in range(count) if i % 2 == 0]


# Functional Programming
def even_numbers_functional(count: int):
    return list(filter(lambda x: x % 2 == 0, range(count)))


# Using
if __name__ == "__main__":
    n = 20
    
    # Object-Oriented Approach
    print("Object-Oriented Approach:", NumberFinder(n).even_numbers())
    
    # Procedural Approach
    print("Procedural Approach:", even_numbers(n))
    
    # Functional Programming
    print("Functional Programming:", even_numbers_functional(n))
```
