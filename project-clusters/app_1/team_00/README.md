# Team 00 - Python Bootcamp

## Magical connections

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Old Style](#exercise-00-old-style)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Shortcuts](#exercise-01-shortcuts)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Greatest Magicians](#exercise-02-greatest-magicians)

<h2 id="chapter-i" >Chapter I</h2>
<h2 id="general-rules" >General rules</h2>

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- We encourage you to create test programs for your project even though this work won't have to be submitted and won't be graded. It will give you a chance to easily test your work and your peers' work. You will find those tests especially useful during your defence. Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

<h2 id="chapter-ii" >Chapter II</h2>
<h2 id="rules-of-the-day" >Rules of the day</h2>

- You should turn in `*.py` files and `requirements.txt` if your code uses third-party modules. Image/HTML file generated in EX02 can also be included, but your code should still be able to produce a similar one.
- It is encouraged to write some tests for various cases inside your scripts as well. To make them run only when script is executed directly and not imported from somewhere else you can use `if __name__ == "__main__":` statement. You can read more about it [here](https://www.geeksforgeeks.org/what-does-the-if-__name__-__main__-do/)
- The work on this day can and should be parallelized. While someone is parsing Wikipedia for EX00, another team member can play around with algorithms for shortest path, and someone else can research the image rendering part.
- Inspiration: [Harry Potter and Methods of Rationality](http://www.hpmor.com/), for playing around with graphs you can try [Gephi](https://gephi.org/).

<h2 id="chapter-iii" >Chapter III</h2>
<h2 id="intro" >Intro</h2>


Albus Percival Wulfric Brian Dumbledore was sitting in his chair and looked on a young boy with 
a lightning bolt-shaped scar on his forehead.

 "So, Harry, you're saying all muggles are connected to each other with just [six handshakes](https://en.wikipedia.org/wiki/Six_degrees_of_separation)?"

 "It is not strictly proven, obviously," Harry straightened his glasses. "But it applies 
 not to just muggles, but everyone!"
 
 "I find this a pretty bold assumption. Any other examples of these... *graphs* you can give me?"
 
 "One of the largest public encyclopaedias in the world is called Wikipedia..."
 
 "It should be a pretty large book! Even a whole series..."

 Harry sighed.

 "It is not a book, it is a website. But the idea is similar to, say, dictionaries - various
 entities are linked to each other..."


<h2 id="chapter-iv" >Chapter IV</h2>
<h3 id="ex00">Exercise 00: Old Style</h3>

During next several minutes, Harry was still explaining to Dumbledore what a 'website' is, but
an old wizard was still unsure about the value of some 'book that can't be touched'.

Harry also tried to explain how some people could follow the links from one article to another and
then end up wondering how did they even get to some other topic. This was a lot easier to relate to
for Dumbledore, and he even started to talk nostalgically about some time when he got completely
lost in a library for a couple of days.

Looks like it was necessary to download some information to illustrate the concept.

-----

You need to write a script called `cache_wiki.py`, which main purpose will be to download pages
from Wikipedia, but the data we're interested in is links in text and 'See also' sections leading
to other pages inside Wikipedia itself. This means, you don't need to download the content, but
only save a graph representation as a JSON file `wiki.json`, so that vertices store pages and
directed edges are links.

You can shoose any Wikipedia article as a default starting position. Also, your code should be
able to receive a name of an existing article as an argument to use instead of a default one
(not necessarily Harry Potter related). So, when it is run like this:

`~$ python cache_wiki.py -p 'Erdős number'`

it should start parsing from [this page](https://en.wikipedia.org/wiki/Erd%C5%91s_number).
Mind the special symbol encoding in URL.

The goal is to keep following links (only those leading to other Wikipedia pages, NOT to the
outside internet) going *at least three pages deep* down every link. This parameter should be
configurable using `-d`, so default value will be `3`. But if the result is too large (>1000 pages)
your code should stop processing links. If it is too small (<20 pages) then please choose some
other default starting page. Don't forget to keep track of the links leading to the pages you've
already visited. If page A links to page B and page B links to page A - it is two directed graph
edges, not one.

Every page your code visits should be logged to stdout using `logging` Python module with log 
level set to 'INFO'. 

There are no strict requirements on the format of JSON file your code produces, but keep in mind
you'll need to work further with this file in next exercises, so you may consider using existing
Python libraries for graph processing, which support reading/writing JSON files.

To earn some extra score for this exercise, your code can also support storing graph in a [Neo4J
database](https://neo4j.com/download/).

<h2 id="chapter-v" >Chapter V</h2>
<h3 id="ex01">Exercise 01: Shortcuts</h3>

 "I see. But why are Welsh Corgi so close to King Solomon?"

Harry wanted to say that he has no idea, but then he noticed the smiling eyes of the wizard. 

 "Frankly speaking, I highly doubt it's the weirdest connection there," said the boy, "but
 don't you think, sir, it's..."
 
 "..absolutely fascinating!" finished the wizard. "I think I've underestimated muggles'
 technologies here, well done. Anyway, but how do we figure out how closely are two pages 
 connected to each other?"

Harry thought for a moment. 

 "I assume we can try and find the shortest path from one page to another. This is a pretty
 complicated task with a regular book, but it becomes a lot easier on a serialized graph."

-----

Now you should write the program called `shortest_path.py`, which will need to find the *shortest*
path length between two pages in your serialized database (if these pages are there):

```
~$ python shortest_path.py --from 'Welsh Corgi' --to 'Solomon'
3
~$ python shortest_path.py --from 'Solomon' --to 'Welsh Corgi' --non-directed
3
```

Mind the `--non-directed` flag. It means we treat all links as 'non-directed' or 'bidirected', so
every edge is treated equally in both directions. In this case, a path exists betweeh *any* two
nodes in your serialized graph.

By default (when `--non-directed` is not specified) we are only following the directed edges of 
the graph. This means, not all pages in the database can be reachable from other pages, especially 
if they  have a small amount of inbound links. If the path doesn't exist, your script should print
'Path not found'.

The location of the wiki file should be read from the environment variable named `WIKI_FILE`. If
the database file is not found, the code should print 'Database not found'.

Additionally, please add `-v` flag, which will enable logging of the found path, like this:

```
~$ python shortest_path.py -v --from 'Welsh Corgi' --to 'Solomon'
'Welsh Corgi' -> 'Dog training' -> 'King Solomon's Ring (book)' -> 'Solomon'
3
```

In this exercise, you shouldn't be using an existing implementation of a 'shortest path'
algorithm provided by an existing libraries. Please write it yourself instead.


<h2 id="chapter-vi" >Chapter VI</h2>
<h3 id="ex01">Exercise 02: Greatest Magicians</h3>

  "Now I can see the relation with "six handshakes" rule you mentioned. Great magicians 
 can be quite popular, right?"

The boy stared at him, trying to understand what's going on in old wizard's head.

 "Oh, Harry, don't you know the definition of popularity? The more fans you have, the more
 well known overall you are. Like with rock bands."

Dumbledore stood up and went to the entrance of the office. Then he stopped right before the door
and turned back to Harry with a smile.

 "I think all we have to do is visualize the data. To find out who's the greatest, I mean."

Harry raised an eyebrow and looked at the wizard in surprise. It was said pretty loud and looked
like Dumbledore was serious. Find out who is the greatest? Okay, from the graph standpoint it
shouldn't be that hard...

...Draco Malfoy managed to escape from being caught eavesdropping. He was hiding around the corner
from the headmaster's office when Dumbledore left, and now his mind was filled with thoughts about
'greatest wizards'. He firmly decided that the next owl he will send to his father will be about 
connecting Malfoy Manor to the Internet.

-----

Your next script `render_graph.py` should render a visualization your graph of pages (from a file
generated in EX00, also reading it from a `WIKI_FILE` env variable) as a PNG image
`wiki_graph.png`, with nodes and edges. You may use any third-party library for that.

The main rule here is that the size of the node should correspond to the number of incoming 
connections. The more connections - the larger the node in render. This way the 'greatest pages'
in your dataset will be the best visible ones.

You can get additional score in this task if your script optionally can generate not only `.png`
file, but also a `wiki_graph.html` page which will show an interactive visualization of the same
graph. You can use libraries like [Altair](https://altair-viz.github.io/) or [Bokeh](https://docs.bokeh.org/en/latest/index.html)
to do that.


**Please leave your feedback [here](https://forms.gle/ZmAjM5qJ3uEnADen6)**
