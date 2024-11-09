# Day 05 - Python Bootcamp

## Wibbly-wobbly, timey-wimey stuff

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Fool Me Once](#exercise-00-fool-me-once)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Screwdriver Song](#exercise-01-screwdriver-song)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Good Timing](#exercise-02-good-timing)
7. [Chapter VI](#chapter-vii) \
    7.1. [Reading](#reading)

<h2 id="chapter-i" >Chapter I</h2>
<h2 id="general-rules" >General rules</h2>

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- We encourage you to create test programs for your project even though this work won't have to be submitted and won't be graded. It will give you a chance to easily test your work and your peers' work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

<h2 id="chapter-ii" >Chapter II</h2>
<h2 id="rules-of-the-day" >Rules of the day</h2>

- You should turn in `*.py` and `requirements.txt` files for this task. You can also add a `README` file explaining how to start your application
- It is encouraged to write some tests for various cases inside your scripts as well. To make them run only when script is executed directly and not imported from somewhere else you can use `if __name__ == "__main__":` statement. You can read more about it [here](https://www.geeksforgeeks.org/what-does-the-if-__name__-__main__-do/)

<h2 id="chapter-iii" >Chapter III</h2>
<h2 id="intro" >Intro</h2>

 "Who was that, Doctor? We barely made out alive!"

 "They are called daleks, one of the most merciless and violent species in the universe. 
 Nevermind though, they can't get us here."

 "In this police box? By the way, why is it bigger on the inside?"

 "TARDIS' Dimensional modeling. Anyway, looks like for this adventure we need more paper
 and we're currently out of it."

 Doctor starts running around the room pulling some levers and pressing some buttons. It looks
 completely random for an untrained eye.

 "Paper? What kind, toilet?"

 "No, that probably wouldn't be a good application. It's psychic paper, see?"

 Doctor immediately shows directly to your face something with a slight resemblance of a passport.
 It says, "Crisis investigator with the UN, Liverpool Division".

 "Are you really with the UN?"

 "With what now? Nevermind. The thing is it shows you what you want to see and can possibly 
 save us some time. And you will need something similar at that place we're going to."

<h2 id="chapter-iv" >Chapter IV</h2>
<h3 id="exercise-00-fool-me-once">Exercise 00: Fool Me Once</h3>

In the next moment two weird-looking devices appear from the Doctor's pockets. One looks like a 
very unusual screwdriver, and the other one is like a smartphone, but with a couple of tentacles
on its sides.

 "So, this is an Ood species detector. When you aim the tentacles at someone it will show
 you the most appropriate name of that species in your language."

You take the device and point its tentacles to the Doctor. The 'smartphone' thinks for a moment
and then the words 'Time Lord' appear on its screen in English.

 "Now, every species in a galactic database has a specific leadership figure or at least 
 some name that will make them stumble for a moment and give you a temporary advantage."

On one of the TARDIS' screens appears a list of species with examples:

```
Cyberman: John Lumic
Dalek: Davros
Judoon: Shadow Proclamation Convention 15 Enforcer
Human: Leonardo da Vinci
Ood: Klineman Halpen
Silence: Tasha Lem
Slitheen: Coca-Cola salesman
Sontaran: General Staal
Time Lord: Rassilon
Weeping Angel: The Division Representative
Zygon: Broton
```

 "Are you joking? Would you believe me if I said to you, out of the blue, that I am
 this... Rassilon?"

 "That's not the point. The point is, most of the creatures will be shocked for a second
 just by the very idea that you would suddenly present yourself like that. This is all we need."

You try to figure out how device works and realize that it actually uses a WSGI+HTTP stack for
presenting results.

Also, while plugging together some cables Doctor gives you one last remark:

 "The Wi-Fi in TARDIS is a bit wonky, you know, especially inside the time stream. So
 currently please don't use any external dependencies."

---

Your goal is to implement a WSGI server with an HTTP wrapper without using any external 
dependencies (see "Reading" section). It should listen on local port 8888 and parse GET
parameters from a URL, for any species title giving you back a JSON (it should be HTTP code 200,
also mind the appropriate 'Content-Type' header and URL encoding). Exaple using cURL might look 
like this:

```
~$ curl http://127.0.0.1:8888/?species=Time%20Lord
{"credentials": "Rassilon"}
```

If it doesn't know the species passed it should return `{"credentials": "Unknown"}` along with
HTTP status code 404

The whole application for this task should be just a single file `credentials.py`.

<h2 id="chapter-v" >Chapter V</h2>
<h3 id="exercise-01-screwdriver-song">Exercise 01: Screwdriver Song</h3>

 "So, what about that over device? Some kinda screwdriver, eh?"

 "Sonic, yes."

 "What can it do? Can I get one?"

 "Well, it generates a combination of certain frequencies, so you can do...pretty much
 anything!"

 "Can it actually unscrew stuff?"

 "Oh, it's kinda tricky. To do that... you know what, here, just play these sound files."

---

This time you need to create a simple WSGI+HTTP client-server application for managing sound files.

First, the server. It shouldn't use any kind of database, just storing files on disk is okay. Web
interface should run on port 8888. When opened, the webpage should show a list of sound files
already uploaded as well as the button for uploading one more. As a user, you should be able to
click on that button, upload the file to the server and it should appear in a list of files shown
on the webpage.

Also, the server should perform a [MIME type](https://en.wikipedia.org/wiki/Media_type) check, so
only audio files are accepted (e.g. `mp3`, `ogg` and `wav`). If a non-audio file is uploaded (e.g.
`jpg`, `exe` or `docx`), it should be discarded and the webpage should show the message "Non-audio
file detected". 

For some bonus points, you can implement playing uploaded sound files directly from the webpage.

This time you are not limited to built-in WSGI server, so it is recommended to use either [Flask](https://flask.palletsprojects.com/)
or [Django](https://www.djangoproject.com/) framework for this task, even though it is not a strict
requirement. Don't forget to add any third-party dependencies you've used into file
`requirements.txt`. Please also include file `README` explaining how to start the HTTP server
(it should contain the specific command to run).

Second, the client. It should be a command-line application with two possible actions:

- `python screwdriver.py upload /path/to/file.mp3` should upload the local audio file
  `/path/to/file.mp3` to the server
- `python screwdriver.py list` should retrieve and print out the names of all the files currently
  present on the server.

All the client-server intercommunication should be using HTTP. It is recommended (though not
strictly required) to use either [Requests](https://docs.python-requests.org/en/latest/) or [HTTPX](https://www.python-httpx.org/) library for
performing HTTP queries.

<h2 id="chapter-vi" >Chapter VI</h2>
<h3 id="exercise-02-good-timing">Exercise 02: Good Timing</h3>

After some time traveling with the Doctor you couldn't say that you can easily be surprised. But 
this time the situation kinda got out of control. Or at least you thought so, looking at five
time lords staying around the TARDIS and aiming at the approaching cybermen. It's not the fact that
it was five of them, more the attempt to grasp that all of them are actually the same person, just
from completely different time periods.

 "Allons-y!" enthusiastically shouts the one in red sneakers. "No destruction, you lot,
 alright?"

 "Obviously. Everyone got their screwdrivers, right?" asks the stern one with gray hair.

 "I think we can damage the control unit, but it's not enough power," says the one in
 leather jacket. "But that's why we are all here, isn't it?"

 "Brilliant!" acknowledges the blonde lady. "So each of us... I mean myself... shall take
 two screwdrivers instead of one and perform a sonic blast!"

The tall one in a fez turns to you and gives you a wink.

 "Just make sure I won't be interfering with myself. You know you can do it. Trust me, I'm
 the Doctor!" Then he looks back at the approaching enemy and adds one more word, "Geronimooo!"

---

Oh boy. There are five unpredictable time lords at our hands. Think of them as threads, so at any
moment in time there is no way to predict which of them will be acting. So you have to synchronize
their actions somehow.

Each Doctor has a screwdriver it his/her right hand, but the required minimum to act is two. So, 
to get two at a time, the Doctor should grab the screwdriver from another Doctor on the left. But
if everybody does it, then nothing is really changed, as every doctor will still have just one 
screwdriver left.

Start by representing both doctors and screwdrivers as Python classes. Doctors are numbered from 
9 to 13, and everyone of them has to make one blast using two screwdrivers.

*NOTE:* this is a variation of a well-known parallel programming problem usually referred to as 
"Dining Philosophers" (see the link in `Reading`).

The output of your threaded program should look like this:
```
Doctor 11: BLAST!
Doctor 9: BLAST!
Doctor 12: BLAST!
Doctor 10: BLAST!
Doctor 13: BLAST!
```

The order may be different on each run, because all Doctors (threads) will be competing with one
another for the next turn to grab two screwdrivers. The code itself should be in file `doctors.py`.

<h2 id="chapter-vii" >Chapter VII</h2>
<h3 id="reading">Reading</h3>

- [WSGI](https://wsgi.tutorial.codepoint.net/intro)
- [Concurrency](https://realpython.com/python-concurrency/)
- [Python Synchronization primitives](https://hackernoon.com/synchronization-primitives-in-python-564f89fee732)
- [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

**Please leave your feedback [here](https://forms.gle/5LkuABmjcwPwj6WX9)**
