# Day 03 - Python Bootcamp

## Computer repair with a smile

Fight the system, help the people!

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [General rules](#general-rules)
2. [Chapter II](#chapter-ii) \
    2.1. [Rules of the day](#rules-of-the-day)
3. [Chapter III](#chapter-iii) \
    3.1. [Intro](#intro)
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00: Innocent Prank](#exercise-00-innocent-prank)
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01: Cash Flow](#exercise-01-cash-flow)
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02: Deploy](#exercise-02-deploy)
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

It was a pretty quiet evening outside, but the work was far from finished inside abandoned arcade. Mobley and Trenton
were in the middle of a fierce debate on various attack vectors, while Darlene was looking at a pinboard with photos
of high members of Evil Corp's management. Elliot was sitting at the corner, while as always mumbling something to
himself. 

 &mdash; Okay everybody, listen up! - Darlene was loud as always, so even arguing hackers shut up immediately. - Let's
 start with small things. We need to show the people that Evil Corp is not to be trusted with their money.

## Chapter IV
### Exercise 00: Innocent Prank

 "Mobley, do you have an example money transfer form?"

 "I sure do. Look at the 'evilcorp.html' file in a shared folder."

 "Perfect. Remember, you can just run `python3 -m http.server` in a directory with this file to be able to test 
 our little prank in a browser. Just open http://127.0.0.1:8000/evilcorp.html and you'll see the form yourself. Then
 Elliot... brother, are you even listening?"

Elliot rotated his chair to show that he's interested.

 "So, you only have one shot at this. Your script will need to modify an actual HTML file on an Evil Corp's 
 server. The more people see the message that they are hacked the better."

Trenton immediately showed a script on her screen that had to be injected into a web page:

```
 <script>
        hacked = function() {
            alert('hacked');
        }
        window.addEventListener('load', 
          function() { 
            var f = document.querySelector("form");
            f.setAttribute("onsubmit", "hacked()");
          },
          false
        );
</script>
```

 "Let's call this operation... [Beautiful Soup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/)!"

-----

You need to write a Python script 'exploit.py' that will do several things:

- First, it needs to read a file "evilcorp.html"
- Second, it should modify page title (in `<title>` tags) to be "Evil Corp - Stealing your money every day"
- Third, it should parse out the name of the user from the page (including the pronoun) and inject new tag `<h1>`
  into a `body` of a page, saying `<h1>Mr. Robot, you are hacked!</h1>`, where 'Mr. Robot' is a parsed pronoun
  and name.
- Fourth, it needs to inject a Trenton's script into a `body` of a page as well. If everything is okay, when
  the 'Send' button is pressed, you should see the word "hacked" appearing in an alert window.
- Finally, the link at the bottom of a page should now lead to "https://mrrobot.fandom.com/wiki/Fsociety" with 
  an actual name of the company on a page replaced with "Fsociety".

The new HTML file should be named "evilcorp_hacked.html" and placed in the same directory as the source
"evilcorp.html" file.

## Chapter V
### Exercise 01: Cash Flow

After a while, Elliot turned his laptop on the table, showing the script. Mobley gave him a thumbs up and 
Trenton exchanged places with Darlene near the pinboard.

 "Well, this is a nice little distraction, but the actual attack will be happening in a different place.
 We know that Evil Corp is using [Redis](https://redis.io/) pubsub as a queue broker. But we only can deploy a
 script once, so..."

 "..So we need a test environment, I get it." Mobley flicked a chunk of popcorn and quickly caught it
 on the fly. "I'm on it."

-----

You need to write two scripts - `producer.py` and `consumer.py`.

Producer needs to generate JSON messages like this:

```
{
   "metadata": {
       "from": 1023461745,
       "to": 5738456434
   },
   "amount": 10000
}
```

and put them as a payload into a Redis pubsub queue. All account numbers ('from' and 'to') should 
consist of exactly 10 digits. Additional points can be earned if the code uses builtin `logging`
module (instead of `print` function) to write produced messages to stdout for manual testing.

Consumer should receive an argument with a list of account numbers like this:

`~$ python consumer.py -e 7134456234,3476371234`

where `-e` is a parameter receiving a list of bad guys' account numbers. When started, it should read
messages from a pubsub queue and print them to stdout on one line each. For accounts from the 
"bad guys' list" if they are specified as a receiver consumer should *swap* sender and receiver for
the transaction. But this should happend *only* in case "amount" is not negative.

For example, if producer generates three messages like these:

```
{"metadata": {"from": 1111111111,"to": 2222222222},"amount": 10000}
{"metadata": {"from": 3333333333,"to": 4444444444},"amount": -3000}
{"metadata": {"from": 2222222222,"to": 5555555555},"amount": 5000}
```

consumer started like `~$ python consumer.py -e 2222222222,4444444444` should print out:

```
{"metadata": {"from": 2222222222,"to": 1111111111},"amount": 10000}
{"metadata": {"from": 3333333333,"to": 4444444444},"amount": -3000}
{"metadata": {"from": 2222222222,"to": 5555555555},"amount": 5000}
```

Notice that only the first line was changed. Second one wasn't because "amount" was negative (even
though receiver is a bad guy). Third one wasn't changed because bad guy is a sender, not a receiver.

## Chapter VI
### Exercise 02: Deploy

 "Perfecto!" Darlene was enthusiastic. "Now all we need to do is write a deployment script."
 
 "I can do that!" Trenton had pretty good [Ansible](https://docs.ansible.com/ansible/latest/index.html) skills. 
 "Once Elliot is inside, all he has to do is install a bunch of packages on a server, copy over our
 exploit and consumer and run them!"

While she were talking, Elliot's fingers were running around on a keyboard, producing a 'todo list',
saving it into 'todo.yml'. Everything was ready.

-----

To complete this exercise, you don't need to actually know Ansible in details. It would be nice if
you could test your code through it, even though it's not strictly required. There is a list of
tasks that should be placed in a generated "deploy.yml" file in YAML format:

- Install packages
- Copy over files
- Run files on a remote server with a Python interpreter, specifying corresponding arguments

These tasks should be generated in Ansible notation (e.g. look [here](https://docs.ansible.com/ansible/latest/collections/ansible/builtin/copy_module.html) for notation
on copying files). The script should be named 'gen_ansible.py'.

Thus, your code should convert Elliot's 'todo.yml' into 'deploy.yml' following this notation.

## Chapter VII
### Reading and tips

Working with HTML is one of the typical tasks when you are writing parsers and various server 
code using Python. Two libraries that are most widely used for this are [lxml](https://lxml.de/) and 
aforementioned [Beautiful Soup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/). They are not mutually exclusive,
though, as lxml can be used as a parsing backend for BS4, combining great performance with pretty
good API flexibility. You can read about parsing backends [here](https://www.crummy.com/software/BeautifulSoup/bs4/doc/#installing-a-parser).

Working with Redis is also a pretty common task to encounter in the world of applied Python. 
And it can also be optimized by using an optional [low-level C wrapper](https://github.com/redis/hiredis-py). It is not a necessary requirement in this task, but still a good module to know about.

Working with YAML is also a very common task, for which [PyYAML](https://pyyaml.org/) is often used. Parsing config
files or writing Ansible plugins is something you can encounter often if Python is used in your 
team as a language for dealing with infrastructure. It would require a lot of time and text to
introduce a specific YAML format for this task, that's why an existing standard is chosen here.
Even though it requires a bit of time and effort to study, it can be really helpful to know the 
very basics of Ansible for your future job or just daily automation tasks.

By the way, just in case you're curious, Ansible [does support Windows](https://docs.ansible.com/ansible/latest/user_guide/windows_usage.html) as well!    

**Please leave your feedback [here](https://forms.gle/dfKBUNyBKs9mvcWYA)**
