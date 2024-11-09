# Day 02 - Python Bootcamp

## Vault 26

Discover the mysteries of a closed Vault!

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Gaining Access](#exercise-00-gaining-access)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Morality](#exercise-01-morality)
6. [Chapter VI](#chapter-vi) \
    6.1. [Reading and tips](#reading-and-tips)

## Chapter I
### General rules

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- We encourage you to create test programs for your project even though this work won't have to be submitted and won't be graded. It will give you a chance to easily test your work and your peers' work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.
- It is recommended to have Python at least version 3.7+ (and definitely NOT <3.4). You can manage different interpreter versions using [pyenv](https://github.com/pyenv/pyenv)
- It is recommended (though not strictly required) that your code is formatted according to [PEP8 style guides](https://peps.python.org/pep-0008/) (modern IDEs can check that automatically). For a short tutorial you can refer e.g. to [this article](https://realpython.com/python-pep8/).
- It is also recommended (though not strictly required) that you use type hinting in your code. You can refer to [this article](https://mypy.readthedocs.io/en/stable/cheat_sheet_py3.html) for a short tutorial.

## Chapter II
### Rules of the day

- You should only turn in `*.py` files
- It is encouraged to write some tests for various cases inside your scripts as well. To make them run only when script is executed directly and not imported from somewhere else you can use `if __name__ == "__main__":` statement. You can read more about it [here](https://www.geeksforgeeks.org/what-does-the-if-__name__-__main__-do/)
- You can guess (or model) the solution for EX01, or you can go through [this small tutorial on Game Theory](https://ncase.me/trust/) to help you with that

## Chapter III
### Intro

The Chosen One stood before a massive door, which was well hidden in an
underground cave stretched deep into the mountain. A closed door, especially
one that never opened during more than a hundred years, is definitely
preserving a mystery. It may be dark and sorrowful, or it may be fun 
and adventurous. These guys may even have a spare GECK!

But our hero's attention was tied to the console next to the door. He slowly
approached it, watching his steps carefully, just in case. Then, pulled an
electronic lockpick (made by Wattz Electronics, Mk2!) from the pocket and 
plugged it into a slot on the side.

The screen lit up and the Chosen One sighed with relief - at least vault's 
reactor was online and this thing still had power. This could be worked with.

But instead of regular hex dumps where he could search for password it showed
something completely unexpected - a set of lines appeared in the screen:

```
AssertionError: len(key) == 1337
AssertionError: key[404] == 3
AssertionError: key > 9000
AssertionError: key.passphrase == "zax2rulez"
AssertionError: str(key) == "GeneralTsoKeycard"

```

Okay, right, the lockpick is programmable. But what the hell is with this
error?


## Chapter IV
### Exercise 00: Gaining Access

Our hero put his backpack on the ground and got out a thick book called
"Dean's Electronics". It mostly covered hardware, but there was a whole
section onprogramming. He read that "assert" is a special statement which
sole purpose is to check if a certain condition is met. Apparently, in this
case the system expected that the introduced digital key would pass several
checks before opening the door.

But it still was weird. First two lines implied that 'key' is a list, but 
then comparing it with number 9000 ruined that assumption completely. Looks
like a custom data type had to be introduced.

At the final chapter, the book also mentioned that custom types can be 
introduced using classes. There was still one thing though - a lockpick
he had had a very tiny memory and couldn't really store 1337 elements in it,
even worse, it couldn't hold 404, either. Was there a way to bypass it?

The last page in this chapter was torn and lost decades ago, only a small
piece left. It just had one line which looked like this:

`__magic_methods__`

with double underscores on both sides.

The Chosen One thought about all this for whole five minutes, then plugged
the lockpick into his trusty PipBoy and started coding.

-----

You need to describe a Python class `Key` so that an instance of this class
would pass the checks listed above. Keep in mind, that your code in this
exercise shouldn't create any containers, neither of size 404 nor less.
Even without it you should be able to pass those checks.

You are encouraged to write an actual set of tests to simulate the key
checking according to the errors above (and to simplify peer review).
This is graded as a bonus.

## Chapter V
### Exercise 01: Morality

Finally, the massive door started to open! Just in case, the Chosen One 
put his hand on the holster. Last time opening such door lead to a long
shootout with ghouls.

But the space behind the door was empty. And clean. In fact, there wasn't
much space there at all - just one small room with a terminal and no way
deeper into the vault. 

The screen on a terminal lit up showing a logo of something called "ZAX 2.0"
and a strange synthetic voice echoed through the room.

 "Greetings, visitor! I see the war has ended and now it's my turn
 to take over!"

Our hero was stunned for a moment, but this wasn't the first time he
encountered a sophisticated security system.

 "Hi, what do you mean by "taking over"?"

 "My name is ZAX and I was created to restore the humanity to its
 glory when the bad times end! Welcome, human, now let's revive the world
 to its glory!"

...After about an hour of discussion the picture started to come together.
ZAX was created by some brilliant scientists long before the war to solve
the problems of distribution of limited resources. When the fallout came
to the horizon, it was reprogrammed based on the same principles to "rule
the world", so to speak, which meant "provide optimizations for supply
chains". Basically, the whole vault was just a single big computer.

The artificial intelligence started asking the Chosen One many questions 
about what's going on on the surface, and also about how long will it take
to bring the current "big shots" here, into the vault, so it could start 
its "life's work".

 "I'm currently processing the thing you people are calling 
 'Prisoner's Dilemma'," acknowledged ZAX. "During my time here based on
 all the information I had I've started classifying people by their
 behavior."

ZAX told about the simple game with candy, where there is a machine that
controls the supply of candy for two groups of people based on whether 
one or both of two operators put one in it:

|  | Both cooperate | 1 cheats, 2 cooperates | 1 cooperates, 2 cheats | Both cheat |
|------------|----------|----------|----------|---------|
| Operator 1 | +2 candy | +3 candy | -1 candy | 0 candy |
| Operator 2 | +2 candy | -1 candy | +3 candy | 0 candy |

So, if everyone is cooperating and puts candy in a machine as agreed,
everyone gets a reward. But both participants also have a temptation to
cheat and only pretend to put a candy into machine, because in this case
their group will get 3 candy back, just taking one candy from a second
group. The problem is, if both operators decide to play dirty, then nobody
will get anything.

Also, ZAX mentioned five models of behavior that it used to run experiments:

| Behavior type | Player Actions                                                                                                                                                                                         |
|---------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Cheater       | Always cheats                                                                                                                                                                                          |
| Cooperator    | Always cooperates                                                                                                                                                                                      |
| Copycat       | Starts with cooperating, but then just repeats whatever the other guy is doing                                                                                                                         |
| Grudger       | Starts by always cooperating, but switches to Cheater forever if another guy cheats even once                                                                                                          |
| Detective     | First four times goes with [Cooperate, Cheat, Cooperate, Cooperate],  and if during these four turns another guy cheats even once -  switches into a Copycat. Otherwise, switches into Cheater himself |

-----

To finish the experiment with ZAX, you need to model a system with seven
classes - `Game`, `Player` and five behavior types (subclassed from `Player`).

The skeleton for a `Game` class looks like this:

```python
from collections import Counter

class Game(object):

    def __init__(self, matches=10):
        self.matches = matches
        self.registry = Counter()

    def play(self, player1, player2):
        # simulate number of matches
        # equal to self.matches

    def top3(self):
        # print top three
```

Here, `registry` is used to keep track of the current number of candy
during the game, while `player1` and `player2` are instances of 
subclasses of `Player` (each being one of 5 behavior types). Calling 
`play()` method of a `Game` instance should perform a simulation
of a specified number of matches between players of a given behavior.

Method `top3()` should print current top three player's behaviors
along with their current score, like:

```
cheater 10
detective 9
grudger 8
```

By default, your code when run should simulate 10 matches (one call of
`play()`) between every pair of two players with *different* behavior
types (total 10 rounds by 10 matches each, no matches between two
copies of the same behavior) and print top three winners after the 
whole game.

You are strongly encouraged to experiment around with different
behaviors and writing your own behavior class (this is graded as a
bonus). You can get even more bonus points if an instance of your 
class performs better in the same "contest between each pair of
players" check that at least three of five provided behaviors.

Don't forget that the only thing a player can do on each turn is
either cooperate or cheat, based on a history of a current game.

-----

...A couple of hours later the Chosen One left the vault with ZAX,
closing the door behind him. He got what he wanted - quite a few new
interesting thoughts to wrap the head around. And about ruling the
world...in its current state the world wasn't ready for something
like ZAX. Not like wild raiders would ever pass the crown to a tin
can. Not like the Chosen One himself would.

## Chapter VI
### Reading and tips

Classes in Python fully support inheritance, but do not provide encapsulation very well. Probably
one of the most interesting things to look at in Python OOP is `super()`, you can read about it 
[here, for example](https://realpython.com/python-super/).

Another thing to read about is a "constructor", which in Python is complex and includes at least 
two methods - `__new__` and `__init__`. Here is [some more information](https://medium.com/thedevproject/new-vs-init-in-python-a-most-known-resource-7beb538dc3b) on topic.   

**Please leave your feedback [here](https://forms.gle/oMEJnwqt5pkLydYy5)**
