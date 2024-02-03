# Day 08 - Python Bootcamp

## Temet Nosce

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: I Know Kung Fu](#exercise-00-i-know-kung-fu)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: A Squid On A Stick](#exercise-01-a-squid-on-a-stick)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: DejaVu](#exercise-02-deja-vu)

## Chapter I
### General rules

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

## Chapter II
### Rules of the day

- You should turn in `*.py` and `requirements.txt` files for this task.

## Chapter III
### Intro

Seraph took a tiny sip from his teacup.

 "You are The One. And your enemy is also one, but many."
 
 "Is this a riddle?" Neo sank down on the nearest bench.
 
 "No. But you need to train fighting against multiple enemies at once."
 
 "I already did that, several times. You just knock out one, then the other..."
 
Seraph raised his hand in a calming gesture.
 
 "You know that real enemies will almost never attack you one by one?"
 
 "Of course. This is not a movie. Just a virtual reality."
 
 "The pause between the moves can be a fraction of a second. You have to keep track of your
 surroundings and switch between appropriate counter actions."
 
Neo also took a sip. Even though he knew the tea was a total fiction, that da hung pao was 
amazing.

## Chapter IV
### Exercise 00: I Know Kung Fu

The good thing about the Matrix is that everything can be simulated. Any situation within the
system is just a program which is written by a human or by a machine for some specific purpose.

That is the reason why Nebuchadnezzar's operator was able to see the actual images behind the 
green letters on the screen. While Neo and Seraph were discussing the training, the code started 
to look similar to this:

```python
import asyncio

from enum import Enum, auto
from random import choice


class Action(Enum):
    HIGHKICK = auto()
    LOWKICK = auto()
    HIGHBLOCK = auto()
    LOWBLOCK = auto()


class Agent:

    def __aiter__(self, health=5):
        self.health = health
        self.actions = list(Action)
        return self

    async def __anext__(self):
        return choice(self.actions)
```

For simplicity, in this training session only four actions are available for both agent and Neo.
The recipe to win in a fight is simple: for every kick Neo has to protect the part (high/low)
where the agent is aiming, and for every block he has to target an unblocked part of the body.

You have to write a script called "fight.py" which will include the unmodified code from above,
but also an asynchronous function 'fight()', that will implement the logic explained above.

The output of the script may look like this (as actions are randomized, an actual result will be 
different on every run):
 
```
Agent: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent Health: 4
Agent: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent Health: 3
Agent: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent Health: 3
Agent: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent Health: 3
Agent: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent Health: 2
Agent: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent Health: 2
Agent: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent Health: 2
Agent: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent Health: 2
Agent: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent Health: 1
Agent: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent Health: 0
Neo wins!
```

BONUS: for additional score, you can write yet another function called 'fightmany(n)', where
instead of one agent Neo will fight a number (a list) of them, so the first line might be:

`agents = [Agent() for _ in range(n)]`

Try to find a way to randomize incoming actions from agents and respond to them appropriately. The 
fight with three agents log may look like this:

```
Agent 1: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 1 Health: 4
Agent 2: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 2 Health: 5
Agent 3: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 3 Health: 4
Agent 3: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 3 Health: 3
Agent 2: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 2 Health: 4
Agent 1: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 1 Health: 4
Agent 2: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 2 Health: 4
Agent 1: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 1 Health: 3
Agent 3: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 3 Health: 3
Agent 3: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 3 Health: 3
Agent 3: Action.LOWKICK, Neo: Action.LOWBLOCK, Agent 3 Health: 3
Agent 1: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent 1 Health: 3
Agent 2: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 2 Health: 3
Agent 2: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 2 Health: 2
Agent 3: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 3 Health: 2
Agent 2: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent 2 Health: 2
Agent 3: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 3 Health: 1
Agent 1: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 1 Health: 2
Agent 1: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 1 Health: 1
Agent 2: Action.HIGHKICK, Neo: Action.HIGHBLOCK, Agent 2 Health: 2
Agent 3: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 3 Health: 0
Agent 2: Action.LOWBLOCK, Neo: Action.HIGHKICK, Agent 2 Health: 1
Agent 1: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 1 Health: 0
Agent 2: Action.HIGHBLOCK, Neo: Action.LOWKICK, Agent 2 Health: 0
Neo wins!
```

## Chapter V
### Exercise 01: A Squid On A Stick

As a program, Seraph dedicated his existence to serving and protecting the Oracle. But one of the
most valuable lessons he taught Neo was not about martial arts at all.

The Matrix is an artificial world. Any interaction within it is not a real kick in real teeth,
but a bunch of bytes sent over the network connection. And all the history of network 
communication for humanity is a competition between attackers and defenders.

And one of the primary weapons in this fight is tracking. Agents track hackers connecting to the
Matrix from the outside. Squiddies are searching for the members of the Resistance. Matrix runners
are looking for the rogue programs that may agree to become invaluable inside agents.

So, let's build a crawler.

For this task, let's be minimalistic. The program should consist of two files - `crawl.py` and 
`server.py`. It is recommended to use [aiohttp](https://docs.aiohttp.org/en/stable/) or [httpx](https://www.python-httpx.org/) for the client
side, and [FastAPI](https://fastapi.tiangolo.com/) for the server side. All the I/O code should be
asynchronous.

The workflow goes like this:
- server is started and listening on port 8888
- client (`crawl.py`) receives one or several queryable URLs as an argument
- client submits all the URLs via HTTP POST request as a JSON list to a server endpoint 
  `/api/v1/tasks/`
- server responds with HTTP 201 created and a task object (consider using [PyDantic](https://pydantic-docs.helpmanual.io/))
- task object includes a status "running" and an ID, which is [UUID4](https://docs.python.org/3/library/uuid.html#uuid.uuid4)
- server then starts asynchronously (do not use threads or multiprocessing) send HTTP GET queries 
  to submitted URLs and collect HTTP response codes, whether it's 200, 404 or some other
- client keeps periodically querying endpoint `/api/v1/tasks/{received_task_id}` until server
  finishes processing all the URLs. Then task status should change to "ready" and task "result"
  field should have a list of HTTP response codes for the submitted URLs
- client prints out tab-separated HTTP response code and corresponding URL for every entry

In synchronous world people often implement this using modules like [Celery](https://docs.celeryproject.org/en/stable/getting-started/introduction.html), but
in this task no external workers are required, so all the server should be in a single Python file,
and all the code should use [async/await paradigm](https://docs.python.org/3/library/asyncio-task.html).

## Chapter VI
### Exercise 02: Deja Vu

 "Whenever one sees a same repeated event twice means it's time to prepare for the worst."
 
Neo thought about this for a moment, but then it dawned on him what Seraph meant.

 "Deja vu is a glitch in the matrix, right?"
 
 "It is more of a sigh of a sudden change of the surroundings."
 
 "So, what are my options in this case?"
 
 "Escape, of course. There is no shame in that. But keeping track of the 'glitching'
 objects also helps."
 
 "In what way?"
 
 "If they are part of the deja vu, that means they are not changed during the upgrade."
 
Neo wanted to ask more questions, but Seraph closed his eyes and politely showed him to the 
door behind him. The Oracle was waiting.

-----

One of the features our crawler is still lacking is caching. If the server saw one of the 
submitted URLs recently, it can just take the cached value for an HTTP code.

Another thing would be to gather some metrics on the input data. Regardless of the fact if
the URL hit the cache or not, let's also count on a server how many requests we've done so
far for a particular domain (e.g. for "https://www.google.com/search?q=there+is+no+spoon" the
domain would be "www.google.com").

You should use Redis for both the cache and domain counters. All the code should still be
asynchronous and use async/await paradigm. You may consider using [aioredis](https://aioredis.readthedocs.io/en/latest/) library
for this task. Since the client code is not affected, you should only submit one file with
a modified EX01 server code called "server_cached.py"

BONUS: Update your code and make another coroutine that will cleanup the entries in cache after
some configurable timeout

**Please leave your feedback [here](https://forms.gle/TV4Nogi9SLYpy88y6)**
