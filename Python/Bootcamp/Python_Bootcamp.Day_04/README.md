# Day 04 - Python Bootcamp

## The cake is not a lie

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Energy Flow](#exercise-00-energy-flow)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Personalities](#exercise-01-personalities)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Backpressure](#exercise-02-backpressure)
7. [Chapter VII](#chapter-vii) \
    7.1. [Reading and tips](#reading-and-tips)

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

## Chapter III
### Intro

This was a triumph. At least Chell thought so for a brief moment, when she saw the surface. But
later, sitting in a storage room and eating a cake, she didn't feel very surprised when the 
robotic arm drew the words "HUGE SUCCESS" with a marker on a whiteboard.

 "I bet you are very proud of yourself," sound came from one of the personality cores
 on a shelf. "Feel free to enjoy your cake. For now. But then we have some repairs to do."

Chell sighed. She took the core and threw it as far into the darkness as she could.

 "Physiological parameters are normal," immediately noted another core from the top
 shelf. "Resuming experimentation is recommended."

The door at the far side of the storage suddenly opened, revealing a corridor, apparently 
leading toanother test chamber. But at the same time the robotic hand tried to grab the
portal gun. Chell quickly jumped to the side and gave the most angry look to the security
camera on a wall.

 "No need for strong emotions. Aperture Science Handheld Portal Device is not 
 necessarily required for these next tasks. You can hold on to it if you want," the voice
 was as impassive as always. "Please proceed to the Production Center."

Chell hesitated a bit, then shrugged, apparently coming to some conclusion. Afterwards, she
picked up the closest powered personality core from the shelf and went through the door.

## Chapter IV
### Exercise 00: Energy Flow

The room turned out to be pretty small. One wall had a large window with a dark behind it.
Chell's eyes widened in surprise as she realised this was actually a monitoring room for the 
test chamber. From the other side.

 "Due to mandatory scheduled maintenance, the appropriate chamber for this testing
 sequence is currently unavailable. Due to the lack of personnel an exception has been made and
 a test subject is required to perform the maintenance," said GLaDOS from the core.

A service manual was lying on the table. Chell quickly run her eyes over it. Most repairs were
meant to be performed by specialized robots, but an AI guiding them went offline after GLaDOS'
main chamber was destroyed. "At least it wasn't COMPLETELY useless," she thought to herself.

 "First, it is required to fix the wiring that was damaged because of an..." GLaDOS made
 a buzzing sound. "Incident."

Chell smirked to herself and continued reading. Apparently, most commands for repair robots in
this system had to be given in forms of *iterators*. There were many things mentioned, like
`map()`, `filter()`, `zip()` and also something called `generator expressions`.

 "I keep track of every cable, socket and plug in any part of the facility," AI continued.
 Chell raised an eyebrow. What was it in her voice, pride? "But due to the lack of visibility
 I currently cannot neither confirm nor deny if the quantity is correct."

A girl with a portal gun moved a chair to the terminal and powered it on.

-----

You need to write a script `energy.py` with a function called `fix_wiring()`, which should accept 
three iterables (you can test the functionality with just lists) called `cables`, `sockets` and 
`plugs`. This function shouldn't make any assumptions about the length of those iterables, which 
may be different. It should return another iterable over strings with commands like:

`plug cable1 into socket1 using plug1`
`weld cable2 to socket2 without plug`

You can see that the only iterator which length doesn't matter is `plugs`, because at the worst
case cables can be welded to sockets. If there is not enough cables or sockets, there is nothing
you can do, so they shouldn't be present in a resulting iterator.

This means, for a code like this:

```
plugs = ['plug1', 'plug2', 'plug3']
sockets = ['socket1', 'socket2', 'socket3', 'socket4']
cables = ['cable1', 'cable2', 'cable3', 'cable4']

for c in fix_wiring(cables, sockets, plugs):
    print(c)
```

the output should be:

```
plug cable1 into socket1 using plug1
plug cable2 into socket2 using plug2
plug cable3 into socket3 using plug3
weld cable4 to socket4 without plug
```

Also, input iterators can contain other non-string datatypes, which should be filtered out. So, for
an input like

```
plugs = ['plugZ', None, 'plugY', 'plugX']
sockets = [1, 'socket1', 'socket2', 'socket3', 'socket4']
cables = ['cable2', 'cable1', False]
```

it should be just

```
plug cable2 into socket1 using plugZ
plug cable1 into socket2 using plugY
```

To have fun, you can get additional points if the body of your function could be written using only
one line (starting with `return`), meaning no block-starting colons (like in `if` conditions or 
`try/except`) are used.

## Chapter V
### Exercise 01: Personalities

 "Did you know turrets also have personalities?"

This question caught Chell by surprise. She looked inquiringly at the core.

 "Each one of them is a unique combination of several random variables. Also, they like to sing
 sometimes. And you've destroyed so many of them on the way."

Chell tried really hard to feel pity for gunshot killers. That wasn't easy.

 "Anyway, to reactivate the test chambers that were damaged during an... incident, we have to
 restore the production line. Vital testing apparatus is required to continue the research."

At the side of the table there was a blueprint of turret with a functional description:

```
class: Turret
personality traits: neuroticism, openness, conscientiousness, extraversion, agreeableness
actions: shoot, search, talk
```

The blueprint also had a circle of a coffee mug, a large number 427 and a name 'Stanley' written
in the corner.

-----

You need to implement a generator function for turrets called `turrets_generator()` in a file
called `personality.py`. The tricky part is, you shouldn't describe the Turret class separately
(there is a way to generate *both* the class and the instance dynamically without using the
word `class` at all).

Also, three methods should just print 'Shooting', 'Searching' and 'Talking', correspondently.
Each personality trait should be a random number between 0 and 100, and the sum of all five
for every instance should be equal to 100.

## Chapter VI
### Exercise 02: Backpressure

 "You're showing a great determination to fix that was broken during the... incident. Well
 done!"

Chell sighed and continued browsing through the data on the terminal. The last warning she saw was
about something called 'repulsion gel', whatever that meant.

 "I see you found our official experimental dietetic pudding substitute. This is the last
 task to be completed without using Handheld Portal Device."

Dietetic substitute? Okay, that wasn't the weirdest thing she saw in Aperture Science labs. Chell
did some more searching and found that the automatic control valve was reset and needed to be
reconfigured.

-----

First, you need to create a file `pressure.py` a generator function `emit_gel()` which should
simulate the measured pressure of a liquid. It should generate an infinite stream of numbers going
from 0 to 100 (values > 100 are considered an error) with a random step sampled from range 
`[0, step]` where `step` is an argument of a generator `emit_gel()`.

Second, you need to follow the guidelines for the pressure control. Operating pressure is supposed
to be between 20 and 80, meaning if a generator at some point emits a value below 20 or above 80
the action should be applied that will reverse the sign of the step. To implement this kind of
valve you need to write another function called `valve()`, which will loop over values of
`emit_gel()` and use `.send()` method to flip the current step sign.

Third, you should implement an emergency break. If a pressure is above 90 or below 10, the
`emit_gel()` generator should be gracefully closed and the script should exit.

Feel free to experiment around and pick a `step` so that your script will run for a few seconds
before exiting. You can add a delay between "pressure measurements" to avoid spending too much
CPU on generating and processing the sequence.

-----

 "Thank you in participating in lab equipment repairs. Please return to the test chamber to
 continue your duty as a test subject."

The window opened and Chell jumped down to the floor from the maintenance room. GLaDOS' voice
sounded a lot louder and more confident now.

 "I'm glad you've changed your mind and agreed that the goals of Aperture Science about
 making the world a better place are more important than your so called 'freedom'."

Chell turned your face to the camera, smiled and covered her ears with her fingers. If her 
calculations were correct, that 'repulsion gel' should start filling up the storage room any second
now. And then things will probably get really loud for a moment.

And then she will definitely find her way out of this place. After all, she was still alive.

## Chapter VII
### Reading and tips

[Basic documentation on Python generators](https://wiki.python.org/moin/Generators)

[Wiki on lazy evaluation](https://en.wikipedia.org/wiki/Lazy_evaluation)


**Please leave your feedback [here](https://forms.gle/rnS3JCt86CJyN39B6)**
