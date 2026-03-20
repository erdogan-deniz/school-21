# Guidelines for tasks

## **Exam**

The task must be solved using a multiparadigm approach.
Use OOP and define classes for examiner, student, and question.
Since processing should happen on different processes, use the `multiprocessing` module.
For generating random values, use the `random` module.
You can select elements from a sequence, assign different weights to elements, etc.
Different weights for different answers should also be assigned to examiners, as they have a defined gender.
For timing and waiting, use the `time` module.
Tables can be drawn in any way, including manually, but one good option is the `prettytable` library, which provides convenient features for this task.

To clear the screen after each iteration so new tables overwrite the previous ones, you can use the command:

```python
import os

os.system('cls' if os.name == 'nt' else 'clear')
```

Then you can easily read points from a file and process them immediately.

You can sum all the points like this:

```python
class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __str__(self):
        return f'{self.x:.1f} {self.y:.1f}'


with open('points.txt', 'r', encoding='utf-8') as f:
    points = map(lambda line: Point(*map(float, line.strip().split())), f)

    print(sum(points, next(points)))
```

Sort students and examiners using the `sorted` function.

In the example above, you can sort points by descending `x`-coordinate like this:

```python
sorted_points = sorted(points, key=lambda point: point.x, reverse=True)
```

Similarly, you can use the `max` and `min` functions with the `key` parameter to determine the maximum and minimum values according to any criterion.

## Image Downloading

This task should be solved using a multiparadigm approach.
To write an asynchronous link handler, use the `asyncio` library.
The actual image downloading process can be implemented using the `requests` library, where the `get` function retrieves the image from the server via the URL.
The received response should be written to a file in bytes.

```python
from requests import get

with open('test.jpg', 'wb') as f:
    f.write(get('https://images2.pics4learning.com/catalog/s/swamp_15.jpg').content)
```

Additionally, you need to handle errors that may occur during the request.
To do this, check the `status_code` of the object returned by the `get` function.
You can verify whether the specified path is correct by attempting to save a file there.
A `PermissionError` exception is raised if there is no access to the specified path.
This task can also be solved using the `grequests` library, which is an asynchronous wrapper over the regular `requests`.Alternatively, you can use the combination of the `asyncio` and `aiohttp` libraries.
