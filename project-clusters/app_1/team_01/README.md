# Team 01 - Python Bootcamp

## Game Night

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Talk and Fight](#exercise-00-talk-and-fight)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: I Like to Move It Move It](#exercise-01-i-like-to-move-it-move-it)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Don't Shoot the Messenger](#exercise-02-dont-shoot-the-messenger)
7. [Chapter VII](#chapter-vii) \
    7.1. [Exercise 03: The Whole Story](#exercise-03-the-whole-story)

## Chapter I
### General rules

- Your scripts should not quit unexpectedly (giving an error on a valid input). If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
- Submit your work to your assigned git repository. Only the work in the git repository will be graded.

## Chapter II
### Rules of the day

- You should turn in `*.py` and `requirements.txt` (if using external dependencies) files for this task.
- For the database you can use PostgreSQL, Redis or just JSON file, in any case you should provide an initial data which can be used to bootstrap the game world on another machine
- Additionally, your project should include a set of documentation (guide) that can be generated using Sphinx (you can refer to DAY07 on what it is and how to use it)
- Also, your project may include various images (make sure to use royalty-free ones, e.g. from websites like https://www.flaticon.com/)

## Chapter III
### Intro

Hello and welcome to Twenty One Software! We are really glad that your team have decided to pursue
a career in game development.

Current market research shows a growth of interest to story-based role-playing games. We count 
on your abilities to create a fully featured project from scratch. The product like that usually 
consists of several pieces that can be developed independently and then combined together. Thus,
we highly encourage your team to split the work.

There are no any restrictions on the universe and setting that you may choose. Some examples:

- Wild West (cowboys, natives)
- Fantasy (dwarfs, elves, dragons)
- Pirates (treasures, parrots, rum)
- Sci-Fi (aliens, cosmos battles, black holes)
- Cyberpunk (corporations, hacking, ghost in the shell)
- My Little Pony (ponies!)

You are not limited to these examples, don't let anyone stop you in inventing your own. Feel free
to unleash your creativity and good luck!

-----

Here's a skeleton for your main class - the Protagonist. During this day, you'll be implementing
different methods for this class and some other classes and wrappers.

```python
from collections import defaultdict


class Protagonist:  # you may decide to add some parent class here, e.g. ORM Model
    def __init__(self, name: str, id: str):  # add more parameters if you need
        self.id = id  # a unique identifier of a current player
        self.name: str = name
        self.hp: int = 10
        # replace with self.level = 1  if you decide to use just level
        self.strength: int, self.craft: int = (1, 1)
        # name and count, modify starting inventory at your wish
        self.inventory = defaultdict(int)
        self.inventory["pocket dust"] += 1  # modify starting inventory as you see fit
    
    def talk_to(self, npc: NPC):
        pass  # you'll need to implement this

    def attack(self, enemy: Enemy):
        pass  # you'll need to implement this

    def take_hit(self, value=1):
        self.hp -= value
        if self.hp <= 0:
            # you'll need to catch this exception in your code and handle this endgame 
            # situation properly, e.g. giving player a meaningful message of what 
            # happened and reset the save so he or she can start again  
            raise Exception("You died")
    
    def heal(self, value=1):
        self.strength: int, self.craft: int = (1, 1)  # starting values may differ
        self.hp += 1

    # can be 'advance_level()' instead. Also, are there any situations in your game
    # where a skill is increased by more than one or even decreased?
    def advance_strength(self, value: int = 1):
        self.strength += value

    def advance_craft(self, value: int = 1):
        self.craft += value

    def go(self, direction: Direction):
        pass  # you'll need to implement this in other exercise

    def whereami(self):
        pass  # returns description of the current location

    def take(self, item: str):
        self.inventory[item] += 1

    def give(self, npc: NPC, item: str):
        self.inventory[item] -= 1
        if self.inventory[item] == 0:
            del self.inventory[item]
        npc.receive(item)
```

## Chapter IV
### Exercise 00: Talk and Fight

Because we are designing an RPG, let's focus on skills and actions. To not become overwhelmed 
with ideas, let's choose one of two simplest skill leveling systems:

1) Your character at the start has a Level 1 at the beginning. Certain actions within the game can
raise protagonist's level. A certain level must be achieved to be able to perform certain actions.
No other explicit skills are used.
2) Your character doesn't have levels, but instead has a set of two skills - Strength and Craft 
(this system is used in some popular board games like [Talisman](https://boardgamegeek.com/boardgame/27627/talisman-revised-4th-edition)).
Certain actions within the game can raise one of those two skills. A certain skill level must be 
achieved to be able to perform certain actions.

As you see in a skeleton above, your character has 10 HP (Health Points) from the start which 
can be increased or decreased based on player's actions.

As you see in the code above, there are at least two more classes to be implemented:

1) NPC (non-playable character)
2) Enemy (those you have to fight with)

If in your game an enemy is a character that you can also talk with, it may make sense to make
`Enemy` a subclass of an `NPC`. 

NPC's, Enemies and their initial stats and phrases should be stored in a 
database (can be PostgreSQL, SQLite or just JSON file on disk). It should be possible to add more 
phrases to a character just by modifying the database. Keep in mind, that in this task all the
initial parameters for NPCs and Enemies should not change during the playthrough, so all the 
players will face the same initial state of the game world. 

The only thing that is a subject to change is a player's profile (e.g. level, inventory, 
location, current line of dialogue or accepted quests), which is also a savegame. That means,
you should design your database structure in such way, that all the changes are only connected 
to `Protagonist` profile in the database.  

One more thing to mention is battles. Enemies should also have skills (levels or Strength/Craft).
Let's make the battle mechanic simple: a virtual six-sided die is rolled for both parties and 
the resulting number is added to a protagonist's (or enemy's) skill level. If the protagonist's 
number is larger, the enemy is defeated. If an enemy wins, protagonist's HP goes down by one. 

It's up to you if the current enemy can immediately be attacked again after the player lost once
already.

Summary: as a result of this stage, several game classes should be implemented (updated 
`Protagonist`, also `NPC` and `Enemy`). Please provide a script `load_data.py` that will 
initialize the database with the parameters and phrases for NPCs and enemies, as well
as a default player profile with a unique ID.

It should be possible to import these classes, make an instance of a Protagonist and (as long 
as the initial data is loaded into the database):
- Create instances of a specific NPC from the database and talk with them
- Exchange items with NPCs (this can work only under certain conditions) - give and take
- Create instances of specific enemies from the database and fight them 

BONUS: implement a quest system so NPCs can give you quests and if you complete them (bring
a specific item, kill a specific monster or pass the message to some other NPC) then you receive
a reward or advance in skill. To do that, you'll have to implement more methods to `Protagonist`
and `NPC` classes. 

## Chapter V
### Exercise 01: I Like to Move It Move It

There is one more type in the `Protagonist` skeleton above that is not implemented in other 
exercises, and this is `Direction`. For simplicity, let's think of the game world as a collection
of interconnected locations, something similar to these marked squares on a 2d plane:

|   | ⬛ |   |   |   |
|---|---|---|---|---|
| ⬛ | ⬛ |   | ⬛ | ⬛ |
|   | ⬛ | ⬛ | ⬛ |   |
|   |   |   | ⬛ |   |

The point of this exercise is to create a set of interconnected locations where the plot 
of your game will unroll. Each location should have a short description (don't mind NPCs and 
items for now, they can be added later) and a list of Directions (pathways) to other locations.
The whole graph of locations should be represented by a structure in the database (including 
links connecting the adjacent locations). This means that the game world structure should be 
modifiable without touching the code, just by updating the entries in the database.

Summary: as a result of this stage, a code should be written that will load the graph of 
locations from the database. One of the locations is marked as a starting location, meaning
the player will spawn there by default in the start of the game. Please provide a script 
called `load_map.py` that will initialize the database with the graph of game locations.

Methods `go()` and `whereami()` should be implemented for a `Protagonist` instance. As a test,
it should be possible to "walk around" the game world loaded from the initial data into the 
database. When a location is walked into, a description is loaded from the database and shown 
to a player (you can just print it in this exercise). 

## Chapter VI
### Exercise 02: Don't Shoot the Messenger

While previous exercises are focused more on game mechanics, this one focuses on an engine.
As the game is turn-based and text-oriented, the good candidate will be a Telegram bot.

There are several Python libraries that allow you to interact with Telegram API. Two most popular
ones probably are:

- [telebot](https://github.com/eternnoir/pyTelegramBotAPI) 
- [aiogram](https://github.com/aiogram/aiogram)

Pick any of these two, and with this tool we will be focusing on one of the most complicated
problems in computer science. It's NAMING things.

Your team is probably already discussing the details about characters and items that would be good
to have in the game. A point of this exercise is to make a bot with a two-level menu to generate 
names for various characters and items. 

First, the menu levels. You probably know Telegram allows the bot to present you with buttons
that you can click. Two main buttons on the top level should be labeled "Characters" and "Items".
Feel free to add emojis to them, if you like. After clicking this button a user should be 
presented with a collection of buttons for various subcategories in a selected category.

For "Characters" it can be, say, "Ponies", "Humans", "Aliens" and "Dwarfs". Practically any
classes, races, genders or other subcategories. For "Items" it may be, say, "Weapons", "Potions", 
"Computer chips" and "Edibles". The only requirement is that these categories fall into the 
narrative that your game is all about. Also, at any menu level deeper than the root, there should 
be an extra button allowing you to get back to the upper level and possibly change your previous 
choice.

Second, the generation algorithm. The simplest one for characters would be to just put together 
a short list of first and last names and then combine them randomly. However, there are no 
limitations and you can implement your own way. Same goes for the items - you can combine
words into something like "Green Magical Sword of Power" or "Rusty Memory Crystal of Hacking".

IMPORTANT NOTE: DO NOT share your Telegram Bot token in your submission. Peer reviewers should be
able to run your bot themselves providing their own token. 

BONUS: use asynchronous (async/await) approach. 

## Chapter VII
### Exercise 03: The Whole Story

Finally, it's time to collect all the pieces. Put together your game as a Telegram Bot, so 
that user can move through the world, talk to NPCs, exchange items, fight enemies and advance in 
skills. This doesn't have to be a long story, but please add all these mechanics (and, optionally,
quests from EX00 bonus section) to be present at least once during the story.

The output of this section should not only be a working game as a Telegram Bot, but also 
a Sphinx-powered documentation with at least two sections, mostly helpful for the peer reviewers:

1) How to start the bot by yourself
2) Game walkthrough following which a player can get from the beginning to the ending 
(or... endings? It's up to you). If they like spoilers, of course.

Also, to not ruin anyone's fun, try to verify it is actually possible to finish the game without 
the walkthrough and any pre-required knowledge whatsoever. 

Please also provide a script `load_all.py` that will initialize the database and populate it with the game data (locations, NPC dialogues and stats, etc.) 

**Please leave your feedback [here](https://forms.gle/591M8fcUEL5idAZB8)**
