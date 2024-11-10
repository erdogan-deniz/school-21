# Day 01 - Python Bootcamp

## Trolling is a art

Help three honorable gentlemen to figure out the better way!

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Functional Purse](#exercise-00-functional-purse)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Splitwise](#exercise-01-splitwise)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Burglar Alarm](#exercise-02-burglar-alarm)  
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
- Your script (or scripts) for this day should have all functions on top level of the file, so they can possibly be imported for checking
- It is encouraged (and graded as a bonus) to write some tests for various cases inside your scripts as well. To make them run only when script is executed directly and not imported from somewhere else you can use `if __name__ == "__main__":` statement. You can read more about it [here](https://www.geeksforgeeks.org/what-does-the-if-__name__-__main__-do/)

## Chapter III
### Intro

 "Fellow gentlemen," started Tom. "I think we can agree that every single thing is determined by a set of features it holds. Like this stone, for example." He knocked on a huge granite boulder he was sitting at. "It has a certain weight, height and proportions, doesn't it?"

 "With all my respect, I disagree," argued Bert. "It's not about its parameters, it's about what it can do, or what you can do with it!"

 "Okay, my friends," interjected William. "Here is my purse." He fished it out of his pocket and put on a large stump near the campfire. A purse made a squeaking sound. "Its main purpose is to store gold ingots. Currently it holds three. Both these things are inseparable when talking about it. Am I wrong?"

 "You are and you arent, honorable William," replied Bert. "The fact that it stores three gold ingots is just its state."

He took a long branch and started drawing letters in the ash of the campfire, like this:

```
purse = {"gold_ingots": 3}

```

 "So, to add a new ingot into a purse, you need to perform a certain action, isn't it?" Bert started writing something like this:

```
def add_ingot(purse):

```

 "Just a tiny second, kind sir," Tom interrupted. "Why do I need to write a function when I can just do it like this?"

He took another branch and drew:

```
purse["gold_ingots"] += 1

```

 "You certainly can, but this means you're making assumptions about a purse that you can't know for sure! What if it is empty, for example? Like..."

```
purse = {}

```

Tom immediately saw his approach didn't work for this case. 

 "That is what I tend to call a [Domain-Driven Design](https://en.wikipedia.org/wiki/Domain-driven_design)," said Bert. "We write specifically what we want to do, and just use standard primitives to help us with that."


## Chapter IV
### Exercise 00: Functional Purse

 "So, Bert, I see you are a distinguished gentleman!" proclaimed William. "So how would you design my purse then?"

You need to write functions `add_ingot(purse)`, `get_ingot(purse)` and `empty(purse)` that accept
a purse (a dictionary, which is, strictly speaking, a `typing.Dict[str, int]`) and return a purse 
(an empty dict in case of `empty(purse)`). They should not make assumptions about the content of 
the purse (it can be empty or store something completely different, like "stones").

Also, your functions shouldn't have side effects. This means, an object passed as an argument 
should not be modified inside a function. Instead, a new object should be returned. Thus, you 
*shouldn't use the code written by Tom*, as it makes a *direct assignment* to a field inside 
a purse. You should return a *new dict instance* with an updated number inside it instead.

So, a function composition like `add_ingot(get_ingot(add_ingot(empty(purse))))` should return
`{"gold_ingots": 1}`. Also, getting an ingot from an empty purse shouldn't lead to an error and 
should just return an empty one.

Side note: we are only interested in gold ingots in this task, so it doesn't really matter what 
happens with the rest of the stuff inside the purse. You can preserve it or throw away.

## Chapter V
### Exercise 01: Splitwise

 "Just wait a moment, kind sirs," said Tom. "How all this will help us split the booty? If after the hunt we have several purses, then how can we decide who gets what?"
 
 "Do not worry, my friend!" William gently slapped Tom on the shoulder. "A guiding star will help us!"
 
 "A star? How?"

 "How does one implement a function so that it can accept both one, two or many objects as arguments?"

 "Oh, I get it now, thank you!" And then Tom and William have started working on an honest algorithm.

You need to write a function named `split_booty`, which will receive any number of purses (dictionaries) as arguments. Purses in arguments can possibly contain various items, but our men of honor are only interested in gold ingots (named `gold_ingots` as in examples above). Number of ingots can be zero or positive integer.

This function should return three purses (dictionaries) back so that in any two of three purses the difference between the number of ingots is no larger than 1. For example, if the booty includes `{"gold_ingots":3}`, `{"gold_ingots":2}` and `{"apples":10}`, then function should return `({"gold_ingots": 2}, {"gold_ingots": 2}, {"gold_ingots": 1})`.

While implementing this function you still shouldn't use direct assignment to fields inside dictionaries. You can reuse functions you wrote in EX00 instead. 

## Chapter VI
### Exercise 02: Burglar Alarm

Bilbo Baggins, or "The Burglar", how he now liked to call himself internally, was hiding in the bushes and quietly listening to three giant trolls, discussing pretty interesting things. He didn't really understand the most of it, but at least it was about booty, purses and ingots. So, he pretty much convinved himself already that this discussion is somehow related to his "specialty", when he decided to steal William's purse. And when his hand was already grabbing it from a stump (trolls were still in the middle of a pretty heated discussion) it suddenly made a very loud squeak.

And he immediately realized that now three pairs of troll eyes are staring directly at him.

 "Sir William," after a short pause started Bert, looking at hobbit who just froze in place out of fear, "I see you've managed to establish some certain protective measures. That's brilliant! Is it some additional feature in your functional design?"

 "Well," William responded, "I believe you've already noted that this particular purse is, so to say, pretty "squeaky". That's because if someone tries some funny business with it then it makes a sound and I immediately know about it. It's due to its specific, hmm, "decoration"..."

 So far you wrote several functions (`add_ingot(purse)`, `get_ingot(purse)` and `empty(purse)`) for the purse design, but now you need to figure out a way to add some new behaviour to all of them - whenever any of them is called a word `SQUEAK` should be printed. The trick is that you can't modify the body of those functions, but still provide that alarm. The clue that William mentioned about "specific decoration" can possibly help you with that.

-----

Even when purse design was perfected and burglar was caught red-handed, trolls couldn't still stop arguing about the approach, whether "action" is less or more important than "feature".

But then it was too late. Or, on the other hand, too early - morning came and first rays of sunlight showed from beyond the horizon. Trolls were almost immediately turned to stone, and Bilbo was finally able to make a sigh of relief when he saw Gandalf approaching from the forest.

 "I knew it was your idea!" hobbit said enthusiastically. "You've imitated their voices so they wouldn't stop arguing, right?"

 "Not really, my honorable Burglar," objected old wizard. "This is what happens when various trolls spend too much time comparing object-oriented programming style with functional programming. But it is some very dark magic you shouldn't really worry about, my friend..."
 
## Chapter VII
### Reading and tips

The rule "do not assign directly" may seem confusing, so here is what's behind it: in functional programming all objects, including data structures, are generally immutable.
That means, it is considered a bad practice to modify the data inside a container, the new container with new value should be created instead.
E.g., if you have a list `a = [1, 2, 3]` and you want to increase the second element by five, instead of writing `a[1] += 5` you should create another object: `b = [a[0], a[1] + 5, a[2]]`.
This approach seems weird, but sometimes when dealing with larger codebase it helps a lot to know that your data won't be accidentally modified at any time somewhere deep in your code, as nothing is mutable.

Also, Python has some immutable object types out of the box. e.g. [frozensets](https://docs.python.org/3/library/stdtypes.html#frozenset).

As an additional cool feature, Python has a built-in way of modifying the behaviour of functions without directly modifying their code.
It is called a `decorator` and is just a special syntax for a function that accepts a function as an argument and returns a function. You can read [this article](https://realpython.com/primer-on-python-decorators/) for more details and examples.  

**Please leave your feedback [here](https://docs.google.com/forms/d/e/1FAIpQLSc9IEAPVeHKnBGZKmG6cZOaQwPX-W0vwa3-mjjm4LsBs0jr3g/viewform?usp=sf_link)**
