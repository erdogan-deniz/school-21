# Simple Bash Utils

Development of Bash text utilities: cat, grep.

The russian version of the task can be found in the repository.

## Contents

0. [Preamble](#preamble)
1. [Chapter I](#chapter-i) \
   1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
   2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
   3.1. [Part 1](#part-1-working-with-the-cat-utility)  
   3.2. [Part 2](#part-2-working-with-grep-utility)  
   3.3. [Part 3](#part-3-bonus-implementation-of-some-grep-utility-flags)  
   3.4. [Part 4](#part-4-bonus-implementation-of-grep-utility-flag-combinations)


## Preamble

![simple_bash_utils](misc/eng/images/bashutils.png)

It was an ordinary grey autumn day in 1993. You came home from work at Hewlett-Packard, feeling a little tired. You had a small two-room apartment on the outskirts of N town. There was a low-alcohol drink in the refrigerator called "pivo". You took that drink and a bag of crackers then went to your little nook, to your computer made by Dell.

`*Click*` - the power button was pressed. A couple of minutes of boot loading and... yeah, it feels good. You always get that feeling when you turn on a computer. A few seconds of undisturbed pleasure and you opened
the Mosaic browser. Then you went to your favorite forum, and while drinking pivo, you read some threads. Suddenly you came across a very interesting discussion, which began with the following message:

> Hello everybody out there using minix -
>
>I'm doing a (free) operating system (just a hobby, won't be big and professional like gnu) for 386(486) AT clones. This has been brewing since april, and is starting to get ready. I'd like any feedback on things people like/dislike in minix, as my OS resembles it somewhat (same physical layout of the file-system (due to practical reasons) among other things).
>
>I've currently ported bash(1.08) and gcc(1.40), and things seem to work. This implies that I'll get something practical within a few months, and I'd like to know what features most people would want. Any suggestions are welcome, but I won't promise I'll implement them :-)
>
>Linus (torvalds@kruuna.helsinki.fi)
>
>PS. Yes - it's free of any minix code, and it has a multi-threaded fs. It is NOT portable (uses 386 task switching etc), and it probably never will support anything other than AT-harddisks, as that's all I have :-(.
>
>— Linus Torvalds

"Very interesting," you thought to yourself. As you scrolled down, you noticed that bash is not that well ported, and some functions didn't work. 
In particular, there were problems with the utilities for word processing: cat and grep.
"Interesting task, and it would be great to help this Linus Torvalds," you said aloud and immediately wrote a message in the thread saying that you're already working on it. 
Well, let’s start!

## Chapter I

## Introduction

In this project you will learn and develop basic Bash utilities for working with C programming language texts. These utilities (cat and grep) are often used in the Linux terminal. As part of the project you’ll learn the organization of the Bash utilities and solidify knowledge of structured programming.


## Chapter II

## Information

### cat History

> cat was part of the early versions of Unix, e.g., Version 1, and replaced pr, a PDP-7 and Multics utility for copying a single file to the screen.

### cat Usage

Cat is one of the most frequently used commands on Unix-like operating systems. It has three related functions with regard to text files: displaying them, combining copies of them and creating new ones.

`cat [OPTION] [FILE]...`

### cat Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

### grep History

> Thompson wrote the first version in PDP-11 assembly language to help Lee E. McMahon analyze the text of the Federalist Papers to determine authorship of the individual papers. The ed text editor (also authored by Thompson) had regular expression support but could not be used on such a large amount of text, so Thompson excerpted that code into a standalone tool. He chose the name because in ed, the command g/re/p would print all lines matching a specified pattern. grep was first included in Version 4 Unix. Stating that it is "generally cited as the prototypical software tool", McIlroy credited grep with "irrevocably ingraining" Thompson's tools philosophy in Unix.

### grep Usage

`grep [options] template [file_name]`

### grep Options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |


## Chapter III

- The programs must be developed in C language of C11 standard using gcc compiler.
- The program code of the cat and grep must be located on the develop branch in the src/cat/ and src/grep/ folders, respectively  
- Do not use outdated and legacy language constructions and library functions. Pay attention to the legacy and obsolete marks in the official documentation on the language and the libraries used. Use the POSIX.1-2017 standard.
- When writing code it is necessary to follow the Google style
- The programs must be executable files with command line arguments
- The programs must be built with Makefile with appropriate targets: s21_cat, s21_grep
- If third-party libraries are used, there must be build scripts in makefile to connect/load them
- Integration tests must cover all flag variants and input values, based on a comparison with the behavior of real Bash utilities 
- The programs must be developed according to the principles of structured programming
- Code duplication must be avoided, common modules must be reused between the utilities. Common modules can be moved to a separate folder src/common
- You can use standard and non-standard C libraries, or you can use your own developed libraries from other projects
- The statement of the message in the case of an error does not matter
- Input via stdin is not required to be supported

## Part 1. Working with the cat utility

You need to develop a cat utility:
- Support of all flags (including GNU versions) specified [above](#cat-options)
- The source, header, and build files must be placed in the src/cat/ directory
- The resulting executable file must be placed in the directory src/cat/ and named s21_cat

## Part 2. Working with grep utility

You need to develop the grep utility:
- Support of the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

## Part 3. Bonus. Implementation of some grep utility flags

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including: `-h`, `-s`, `-f`, `-o`
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep

## Part 4. Bonus. Implementation of grep utility flag combinations

Bonus assignment for extra points. You need to develop the grep utility:
- Support of all flags, including their _pair_ combinations (e.g. `-iv`, `-in`)
- Only pcre or regex libraries can be used for regular expressions
- The source, header and make files must be placed in the src/grep/ directory
- The resulting executable file must be placed in the directory src/grep/ and named s21_grep



💡 [Tap here](https://forms.yandex.ru/u/6357b8eed04688262d1f10cd/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.


