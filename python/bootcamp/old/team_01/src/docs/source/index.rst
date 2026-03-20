**The Escape From Cyber The World documentation!**
===================================================

**Создание документации**
--------------------------

Для создания документации необходимо:

- Установить необходимые модули прописав команду `pip install -r requirements.txt`;
- Ввести комманду `make html` в папке `docs`.

**Подготовка проекта**
-----------------------

Для создания базы данных Вам нужно:

- Установить `postgres-client` введя команду `sudo apt install postgresql-client`;
- Установить `postgres` введя команду `sudo apt install postgresql`;
- Создать пользователя `postgres` введя команду `sudo -i -u postgres`;
- Зайти в консоль `psql` введя команду `psql`;
- Создать базу данных `Team01` введя команду `create database "Team01";`;
- Задать базе данных пользователя `postgres` введя команду `ALTER DATABASE Team01 OWNER TO postgres;`;
- Установить пароль базе данных командой `ALTER ROLE postgres WITH LOGIN ENCRYPTED PASSWORD '196910';`.

**Запуск программы**
---------------------

Для запуска самой программы Вам нужно:

- Создать базу данных;
- Находиться в папке `src`;
- Установить все необходимые пакеты командой `pip install -r requirements.txt`;
- Создать свой токен бота в `@BotFather`;
- Создать свой токен и ввести его в `bot_data.py`;
- Прописать команду `python load_all.py`, чтобы создать таблицы, заполнить их данными;
- Прописать команду `python start.py`;
- Вся остальная работа осуществляется в боте после запуска скриптов.

**Общее описание**
-------------------

*Welcome to the turn-based RPG game Escape from the cyber world.*

The whole gameplay is based on interaction with the bot. A chatbot is used as the interaction interface, in which you can:

- Read the description of entities (map, enemy, NPC);
- Select an available action (moving, fighting, taking a task, handing over a task, talking, selecting an object, exiting a trap, ...);
- See an image of the location.

Brief briefing
~~~~~~~~~~~~~~~

First you should press the `"/ start"` button or enter the `"/ start"` command into the chat. 

After that, you will be asked:

- Familiarize yourself with the map (by directly switching between locations);
- Go to the settings and games section.

In the settings section, you can select:

- Character type (with its own characteristics);
- The initial item (with its own buffs).

At each point, there is an opportunity to take a step back. Whatever point you left, your settings are saved.

You can also start the game from the settings menu.

When you are at the last location, you can get out of the world with an electronic key, which you must receive for completing the task. 

There are trap locations on the map, once in which you instantly die.

You can level up by completing a task or killing an enemy.

To get to the final enemy, you need a third level.

You can take two tasks: one to kill an enemy, one to bring an artifact.

All enemies can be fought.

You can talk to all NPCs.

Cледующие разделы
""""""""""""""""""

.. toctree::
   :maxdepth: 3

   ./manual.rst
   ./doc.rst
