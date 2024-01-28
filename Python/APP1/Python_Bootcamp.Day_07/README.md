# Day 07 - Python Bootcamp

## Is there a difference?

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Retirement Plan](#exercise-00-retirement-plan)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Human Life](#exercise-01-human-life)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: For the Future](#exercise-02-for-the-future)
7. [Chapter VI](#chapter-vii) \
    7.1. [Reading](#reading)

<h2 id="chapter-i" >Chapter I</h2>
<h2 id="general-rules" >General rules</h2>

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

<h2 id="chapter-ii" >Chapter II</h2>
<h2 id="rules-of-the-day" >Rules of the day</h2>

- You should turn in `*.py` and `requirements.txt` files for this task, as well as a "database" file with questions and "tests" and "docs" folders with corresponding content.
- The documentation from EX02 should be buildable by `make html` command

<h2 id="chapter-iii" >Chapter III</h2>
<h2 id="intro" >Intro</h2>

 "It seems you feel our work is not a benefit to the public."
 
 "Replicants are like any other machine. They're either a benefit or a hazard. If they're a benefit, it's not my problem."
 
 "May I ask you a personal question?"

Deckard sat down on a chair.
 
 "Sure."
 
 "Have you ever retired a human by mistake?"
 
 "No," he didn't even blink.
 
 "But in your position that is a risk?"

Deckard prepared to give some meaningful response, but then another person appeared in the room.
It was a tall man, presumably in his fifties, wearing an impeccable black suit and some kind of 
advanced tech multifaceted glasses.

<h2 id="chapter-iv" >Chapter IV</h2>
<h3 id="exercise-00-retirement-plan">Exercise 00: Retirement Plan</h3>

 "Is this to be an empathy test? Capillary dilation of the so-called blush response?
 Fluctuation of the pupil? Involuntary dilation of the iris?"

 "We call it Voight-Kampff for short."

Rachael decided to keep the formalities.

 "Mr. Deckard, Dr. Eldon Tyrell," she introduced.

 "Demonstrate it. I want to see it work," Tyrell seemed to be impatient. A characteristic
 of people with a very busy schedule.

Several minutes have passed and discussion went on. Even being young and bold, Deckard came to
realize that the Voight-Kampff test is far more dangerous than it seems. There had to be a lot of 
work put into it to make it reliable.

-----

You have to design your own version of [Voight-Kampff test](https://bladerunner.fandom.com/wiki/Voight-Kampff_test).
For this you should prepare a set of questions (at least 10 is enough) with three or four responses
to randomly choose from. These questions and answers should be stored in a separate file of any
format (e.g. SQLite or simply JSON).

After each response a set of variables should be typed in manually by a person
asking questions:

- Respiration (measured in BPM, normally around 12-16 breaths per minute)
- Heart rate (normally around 60 to 100 beats per minute)
- Blushing level (categorical, 6 possible levels)
- Pupillary dilation (current pupil size, 2 to 8 mm)

After ten questions and variable measurements, the test should print out a strict binary decision
whether a responding subject is a human or a replicant. In this exercise, you can invent your own
logic to use for making this decision.

Try to split your business logic into separate files based on tasks components solve. The starting 
script should be called `main.py`. All interaction with the test should work via command line.

<h2 id="chapter-v" >Chapter V</h2>
<h3 id="exercise-01-human-life">Exercise 01: Human Life</h3>

During a couple of days after interaction with Rachael and Tyrell, Deckard couldn't stop thinking
about the reliability of the test. He always blindly followed its results, but could he trust the
test itself?

All the research led him to the fact that human body does have surprisingly few responses to an
external stimulus that could be called 'fully automatic'. Of course Rick couldn't reproduce the
whole research behind Voight-Kampff, but he wanted to know the algorithm.

Deckard couldn't really explain why, even to himself. One of the most dangerous thoughts was,
"I need to know the proper answers if I am ever to be a test subject".

-----

You already have the implementation of the test from EX00. But does it really work properly?
In this exercise, you need to write tests to cover all the possible positive and negative cases.

What if the file with questions is empty? Could it be that there is an equal probability for an
output to be human or replicant based on the data?

Your VK test implementation most likely consists of several functions and, supposedly, classes.
Your goal here is to cover all the corner cases for all the components with tests. Basically, 
whenever a test operator inputs something wrong (like, selecting non-existent answer or
out-of-bounds numbers for measurements, e.g. negative heart rate) he or she should receive a
meaningful information message and a possibility to repeat the input.

During this exercise you will most likely rewrite at least some of the code from EX00, but that's
the whole point. Also, it is highly recommended to use Pytest framework when writing tests (see 
Reading section below). All the tests should be inside `tests` directory.

<h2 id="chapter-vi" >Chapter VI</h2>
<h3 id="exercise-02-for-the-future">Exercise 02: For the Future</h3>

...But did it matter? After all what happened in the next week, the line separating humans and
replicants has practically disappeared for Deckard. He knew it existed, because the test said 
it existed, but that was about all he had.

Blade runners still had to use the test when hunting the escaped replicants. It was their 
way to make sure that they are doing the right thing.

 "What are you working at?" Rachael asked him one day. 

 "I want... to write about it. I think it's more of an art piece for me now, rather than a
 weapon."

 "You've never answered me... Did you ever take that test yourself?"

 "Don't worry about it. Cogito, ergo sum."

-----

You need to use Sphinx project to auto-generate documentation for your code written in EX00/EX01.

The resulting documentation should consist of at least two parts:

- Quickstart, which is the description of how to work with the test
- Auto-generated reference over the code (see link to Sphinx Autodoc in Reading section)

For the first part, you can use either Markdown or RST for the text and formatting.
For the second part, you'll need to add comments to all entities in your code - modules,
functions, classes, etc. You can find a link to the guide on how to write docstrings in Reading
section.

You should also add a proper title and logo to your project for the documentation. Don't include 
the generated docs into your submission though, it should be buildable with `make html` on your 
peer's side if all the requirements are installed.

<h2 id="chapter-vii" >Chapter VII</h2>
<h3 id="reading">Reading</h3>

[Python Testing Guideline](https://realpython.com/pytest-python-testing)
[Python Sphinx Tutorial](https://www.sphinx-doc.org/en/master/tutorial/index.html)
[Writing Docstrings](https://realpython.com/documenting-python-code/)
[Sphinx Autodoc](https://www.sphinx-doc.org/en/master/usage/extensions/autodoc.html)

**Please leave your feedback [here](https://forms.gle/YEzd846qsykVaShq8)**
