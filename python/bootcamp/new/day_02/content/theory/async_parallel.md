# **Asynchronous and Parallel Programming**

Asynchronous and parallel programming are techniques that allow multiple tasks to run concurrently, improving a program’s efficiency and performance depending on the type of task and available resources.

## **Parallel Programming**

Parallel programming enables multiple tasks to be executed simultaneously by distributing them across multiple processors or processor cores.
In Python, the `multiprocessing` module is commonly used for parallel programming.
It allows for the creation of processes that run independently and provides mechanisms for data exchange between processes and parallel task execution.
Let’s look at an example of a program that creates a queue to transfer data between input/output and a worker process.
Suppose the program allows the user to input numbers via the keyboard, which are then written to files by another process.

```python
import multiprocessing
import time


def process(i: int):
    """
    Function representing a processing task.
    Waits i seconds and writes a line to a file named {i}.txt.
    :param i: Processing time, number to save.
    :return
    """

    time.sleep(i)

    with open(f"{i}.txt", "w", encoding="utf-8") as file:
        file.write(f"Hello, {i}!")


def worker(queue: multiprocessing.Queue):
    """
    Continuously extracts items from the queue and sends them for processing via the process function.
    :param queue: Queue of items to process.
    :return:
    """

    while True:
        process(queue.get())


def iostream(queue: multiprocessing.Queue):
    """
    Waits for console input until a non-numeric value is entered.
    Entered numbers are added to the queue for further processing.

    :param queue: Queue of items to process.
    :return:
    """

    while True:
        n = input("Enter a number: ")

        if not n.strip().isdigit():
            break

        queue.put(int(n))


def main():
    """
    Creates a separate process for processing items and waits for its completion.
    Also handles the main process.
    :return:
    """

    #  Create a queue of items to process
    queue = multiprocessing.Queue()

    # Process creation
    worker_process = multiprocessing.Process(target=worker, args=(queue,))

    # Process in a separate process
    print("Starting work")
    worker_process.start()

    # Input in the main process
    iostream(queue)

    # Wait for processing remaining items in the queue
    print("Finishing work")

    while not queue.empty():
        pass

    # Terminate the process
    worker_process.terminate()

    while worker_process.is_alive():
        pass

    worker_process.close()
    print("Work ended")


if __name__ == "__main__":

    # Run the main function
    main()

```

## Asynchronous Programming

Asynchronous programming allows creating efficient and responsive programs that do not block while waiting for I/O operations or other delays to complete.
In Python, this is achieved using the asyncio module.
It provides tools for writing asynchronous code using the async and await keywords.
The module is based on the concept of coroutines and enables parallel execution of multiple tasks within a single thread.
Consider an example program that creates a queue to transfer data between input/output and a worker process.
The program allows the user to input numbers from the keyboard, which are then asynchronously written to files.

```python
import asyncio
from contextlib import suppress
from aioconsole import ainput


async def process(i: int):
    """
    Asynchronous function representing a processing task.
    Waits i seconds and writes a line to a file named {i}.txt.
    :param i: Processing time, number to save.
    :return:
    """

    await asyncio.sleep(i)

    with open(f"{i}.txt", "w", encoding="utf-8") as file:
        file.write(f"Hello, {i}!")


async def worker(queue: asyncio.Queue):
    """
    Asynchronous worker process that continuously takes items from the queue
    and sends them to the process function.
    :param queue: Queue of items to process.
    :return:
    """

    while True:
        i = await queue.get()

        await process(i)
        queue.task_done()


async def iostream(queue: asyncio.Queue):
    """
    Asynchronous process that waits for console input until a non-numeric value is entered.
    Entered numbers are added to the queue for further processing.
    :param queue: Queue of items to process.
    :return:
    """

    while True:
        n = await ainput("Enter a number: ")

        if not n.strip().isdigit():
            break

    await queue.put(int(n))


async def manager(
    queue: asyncio.Queue, iostream_task: asyncio.Task, worker_task: asyncio.Task
):
    """
    Manager coordinates between input/output and worker process.
    Waits for iostream completion and processing of queued items, then stops the worker.
    :param queue: Queue of items to process.
    :param iostream_task: Input/output task.
    :param worker_task: Worker task.
    :return:
    """

    await iostream_task
    print("Finishing work")
    await queue.join()
    worker_task.cancel()
    await worker_task


async def main():
    """
    Main function that creates asynchronous tasks for I/O, worker, and manager and waits for their completion.
    :return:
    """

    # Creating a queue of elements for processing
    queue = asyncio.Queue()

    # Creating tasks
    worker_task = asyncio.create_task(worker(queue))
    iostream_task = asyncio.create_task(iostream(queue))
    manager_task = asyncio.create_task(manager(queue, iostream_task, worker_task))

    # Run multiple tasks concurrently
    print("Starting work")

    with suppress(asyncio.CancelledError):
        # Suppress CancelledError (raised when a task is cancelled)
        await asyncio.gather(iostream_task, worker_task, manager_task)


print("Work ended")

if __name__ == "__main__":
    # Run the main function
    asyncio.run(main())
```

> **Note:** In asynchronous code, only a single thread of execution is used, and the standard `input` function will block it. There is a library called **`aioconsole`** that handles console I/O correctly at a low level.
This allows you to avoid blocking the event loop by using `ainput` with `await` instead of the regular `input`.
