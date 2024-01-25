# Day 06 - Python Bootcamp

## That Kind of Battle Training

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Kirov Reporting](#exercise-00-kirov-reporting)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Data Quality](#exercise-01-data-quality)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Keeping Records](#exercise-02-keeping-records)
7. [Chapter VI](#chapter-vii) \
    7.1. [Reading](#reading)

<h2 id="chapter-i" >Chapter I</h2>
<h2 id="general-rules" >General rules</h2>

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- We encourage you to create test programs for your project even though this work won't have to be submitted and won't be graded. It will give you a chance to easily test your work and your peers' work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

<h2 id="chapter-ii" >Chapter II</h2>
<h2 id="rules-of-the-day" >Rules of the day</h2>

- You should turn in `*.py`, `*.proto` and `requirements.txt` files for this task. Also, optionally, config files and migrations for Alembic, if you decide to go for a bonus. You can also add a `README` file explaining how to start your application
- It is encouraged to write some tests for various cases inside your scripts as well. To make them run only when script is executed directly and not imported from somewhere else you can use `if __name__ == "__main__":` statement. You can read more about it [here](https://www.geeksforgeeks.org/what-does-the-if-__name__-__main__-do/)

<h2 id="chapter-iii" >Chapter III</h2>
<h2 id="intro" >Intro</h2>

 "You wanted to see me, sir?"

 "Yes, Wiggin, we have some work to do. Today I want to teach you how to calibrate our
 battle simulator equipment based on scanners and information reports from battleship commanders."

 "With all my respect, sir, shouldn't we also invite other members of my squad?"

  "This is not a kind of task that requires a lot of people to deal with. Also, as a future
 commander it is necessary for you to know your tooling. Everything clear?"

 "Sir, yes, sir!"

Ender started to read through the project documentation. It turns out, there is a ton of scanners
and detectors Federation deployed across the galaxy to monitor various sectors of space and keep
track of all the spaceships currently going through, both allies and enemies. 

Every spaceship had several characteristics:

- Alignment (Ally/Enemy)
- Name (can be 'Unknown' for enemy ships)
- Class, which is one of {Corvette, Frigate, Cruiser, Destroyer, Carrier, Dreadnought}
- Length in meters
- Size of the crew
- Whether or not the ship is armed
- One or more officers responsible for the ship

It looked like the system should consist of three architectural layers:

- Transport layer
- Validation layer
- Storage layer

Each of these layers will need to have its own representation of what a spaceship is and how to
process it.

And Colonel Graff will keep silently watching the boy's actions from the bridge the whole time.
Even though Ender kinda got used to it already.

<h2 id="chapter-iv" >Chapter IV</h2>
<h3 id="exercise-00-kirov-reporting">Exercise 00: Kirov Reporting</h3>

The main protocol used for interspace communication was called 'Protobuf 2.0'. The entries were
being sent over the transport called 'gRPC'. So, this was the first layer Ender had to implement.

As gRPC is a client-server communication framework, two components had to be implemented - 
'reporting_server.py' and 'reporting_client.py'. The server should provide a response-streaming
endpoint, where it receives a set of coordinates (Ender was allowed to use [any particular system](https://en.wikipedia.org/wiki/Astronomical_coordinate_systems)
he likes), and responds with a stream of Spaceship entries.

As this is currently a test environment, even though every Spaceship should still have all the 
parameters mentioned, they could be random. Also, they should be strictly typed, e.g.:
 
 - Alignment is an enum
 - Name is a string
 - Length is a float
 - Class is an enum
 - Size is an integer
 - Armed status is a bool
 - Each officer on board should have first name, last name and rank as strings

The number of officers on board is a random number from 0 (for enemy ships only) to 10.

The workflow should go like this:

1) the server is started
2) the client is started given a set of coordinates in some chosen form, e.g.:
    
`~$ ./reporting_client.py 17 45 40.0409 −29 00 28.118`

  An example given is galactic coordinates for [Sagittarius A\*](https://en.wikipedia.org/wiki/Sagittarius_A*)
3) these coordinates are sent to the server, and server responds with a random (1-10) number
  of Spaceships in a gRPC stream to the client
4) the client prints to standard output all the received ships as a set of serialized JSON
  strings, like:

  ```
  {
    "alignment": "Ally",
    "name": "Normandy",
    "class": "Corvette",
    "length": 216.3,
    "crew_size": 8,
    "armed": true,
    "officers": [{"first_name": "Alan", "last_name": "Shepard", "rank": "Commander"}]
  }
  {
    "alignment": "Enemy",
    "name": "Executor",
    "class": "Dreadnought",
    "length": 19000.0,
    "crew_size": 450,
    "armed": true,
    "officers": []
  }
  ```

NOTE: this output here is formatted for readability, your code can still print one JSON per string

<h2 id="chapter-v" >Chapter V</h2>
<h3 id="exercise-01-data-quality">Exercise 01: Data Quality</h3>

 "Sir, can I ask a legitimate question?"

 "At ease, Wiggin, what do you have there?"

 "I think that sending the signal through space is a process that can be prone to errors.
 Shouldn't we check that the entries we receive are real and not just some phantoms and
 malformed data?"

 "Good thinking, cadet. There is an information about ships' classes in the registry.
 Just drop whatever entries seem to be malformed."

Ender brough on the screen a list of classes with specific parameters:

| Class       | Length     | Crew    | Can be armed? | Can be hostile? |
|-------------|------------|---------|---------------|-----------------|
| Corvette    | 80-250     | 4-10    | Yes           | Yes             |
| Frigate     | 300-600    | 10-15   | Yes           | No              |
| Cruiser     | 500-1000   | 15-30   | Yes           | Yes             |
| Destroyer   | 800-2000   | 50-80   | Yes           | No              |
| Carrier     | 1000-4000  | 120-250 | No            | Yes             |
| Dreadnought | 5000-20000 | 300-500 | Yes           | Yes             |

The boy decided to represent these limitations as Pydantic data types (see Reading section).

That way it will not just be easier to validate incoming data, but also serialization to JSON
becomes a lot easier. He decided to make another version of the client ('reporting_client_v2.py'),
which will work with the same server. But this time it should validate the stream of Spaceships 
using Pydantic and filter out those which have some parameters out of bounds, according to the 
table above. The rest should be printed exactly as in EX00.

Additionally, from the first part Ender already knew that Name could be 'Unknown' ONLY for enemy
ships.

<h2 id="chapter-vi" >Chapter VI</h2>
<h3 id="exercise-02-keeping-records">Exercise 02: Keeping Records</h3>

How good are reports if we are not storing them? For the last Storage layer there had to be yet
another representation of a Spaceship, now as an ORM model (or a set of models, he thought, 
remembering about officers).

Now Ender's project will have to include 'reporting_client_v3.py' script which is responsible
for mapping incoming objects to a database via ORM.

The third version of the client should now not only print out filtered list of spaceships, but also
save them to PostgreSQL database (avoiding storing duplicates, as Name combined with a set of
officers is a unique combination). It is okay if database and user for PostgreSQL are created
manually, as long as there is a description in comments/text file in the submitted project.

Another case that colonel asked Ender to implement was searching for 'traitors'. Sometimes the same
officers (with unique combination of first name, last name and rank) may have been encountered
both on ally and enemy ships. So, the scan interface in version 3 should look like this (mind the 
word 'scan'):

`~$ ./reporting_client.py scan 17 45 40.0409 −29 00 28.118`

And listing of traitors would be

`~$ ./reporting_client.py list_traitors`

which should print a list of JSON strings with "traitors'" names:

```
{"first_name": "Lando", "last_name": "Calrissian", "rank": "Entrepreneur"}
{"first_name": "Red", "last_name": "Guy", "rank": "Impostor"}
```

OPTIONAL BONUS: Graff also proposed Ender to think about what happens if the storage format will
change. Try using Alembic (see Reading section) to generate migrations to bootstrap your database
and then an additional migration with adding the optional "speed" field to the Spaceship model.

<h2 id="chapter-vii" >Chapter VII</h2>
<h3 id="reading">Reading</h3>

[Protocol Buffers using Python](https://developers.google.com/protocol-buffers/docs/pythontutorial)
[gRPC using Python](https://grpc.io/docs/languages/python/basics/)
[Pydantic Models](https://pydantic-docs.helpmanual.io/usage/models/)
[SQLAlchemy](https://docs.sqlalchemy.org/en/14/orm/tutorial.html)
[Alembic](https://alembic.sqlalchemy.org/en/latest/tutorial.html)

**Please leave your feedback [here](https://forms.gle/xEbk5Q1jZjn3hqci6)**
