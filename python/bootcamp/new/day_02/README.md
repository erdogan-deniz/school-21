# Day 02: *Python* bootcamp

Summary: you'll use object-oriented, procedural and multiparadigm approaches in *Python*.
You'll write code that follows the *functional programming paradigm*.

## General information

Topics to explore:

- **Procedural approach** — a programming style in which tasks are procedures or functions.
- **Asynchronous and parallel programming** — a techniques for running multiple tasks simultaneously.
- **Multiparadigm approach** — a programming style which combining multiple programming paradigms within a program.
- **Object-Oriented Programming (OOP)** — a programming paradigm that structures and organizes code as objects that interact.
- **Functional paradigm** — a programming paradigm that focuses on defining and applying functions that transform data without altering the original values.

## Exercise 01: exam

Students are lining up to take an exam.
Examiners are working simultaneously.
Students wait in a single queue.
When examiner becomes available, the next student in line goes in for their exam.
`30` after an exam begins, examiner is permitted to take a lunch break.
They finish the session, after they refuse students for a random duration between `12` and `18` seconds.

The exam process works:

- Student is asked `3` questions from a question bank.
- For each question, the student randomly selects a word from the question as answer.
  Boys choose words closer to the beginning of the question.
  Girls choose words closer to the endof the question.
  The probabilities follow a *golden ratio* distribution.

  For example:
  In response to the question `There is a table`, a boy would answer `There` with probability `a = 1 / F`, `is` with probability `b = (1 – a) / F` and `table` with probability `c = 1 – a – b`, where `F ≈ 1.618...`.
  A girl answering the question would choose `table` with probability `a`, `is` with probability `b` and `There` with probability `c`.

- Since examiners do not know the correct answer, they randomly select words from the question.
  Multiple correct answers are allowed.
- After selecting answer, the examiner has a `1 / 3` chance of selecting another answer and continues this process until all the words in the question have been selected as correct or the examiner stops.
- Once the student has answered, the examiner decides whether the student passed the exam.
  There is a `1 / 8` chance that the examiner is in a bad mood (the student automatically fails), a `1 / 4` chance that the examiner is in a good mood (the student automatically passes) and a `5 / 8` chance that the examiner is in a neutral mood.
  In that case, the outcome depends on performance: the student passes if they answered more questions correctly.
  The exam's duration depends on the length of the examiner's name.
  
  For example:
  An examiner named `Stepan` would conduct exams lasting between `5` and `7` seconds (a random float in range).

You need to simulate the exam process.

When the program starts:

- The list of examiners is read from the `examiners.txt` file.
- The list of students who arrived early and formed a queue is read from `students.txt`.
- The question bank is read from the `questions.txt` file.

The exam begins.
Each examiner conducts exams on a separate process.
During execution, the console display up-to-date exam information:

1. **Table of students** with two columns: `Student` and `Status`.
   The status can be one of: `In queue`, `Passed`, `Failed`.

   The table must be sorted by status:

   - First, students in the queue in the order they’ll be examined
   - Second, those who passed
   - Third, those who failed

2. **Table of examiners** with five columns: `Examiner`, `Current student`, `Total students`, `Failed`, `Work time`.
   When an examiner is on a break or has finished for the day, display `-` in the `Current student` column.
3. A separate line showing the number of students in the queue out of the total.
4. A separate line displaying the time since the exam started.

This information updated in place, not printed as new lines.

When the exam ends and program stops, display:

1. **Table of students** with two columns: `Student` and `Status`.
    Status is only `Passed` or `Failed`.
    The table is sorted with `Passed` first and `Failed` last.
2. **Table of examiners** with four columns: `Examiner`, `Total students`, `Failed`, `Work time`.
3. A separate line showing the total time from the start to the finish of the exam.
4. A separate line listing top-performing students, separated by commas.
5. A separate line listing top examiners, comma-separated.
6. A separate line listing students to be expelled.
   These are the students who failed and finished earlier than other students who failed.
7. A separate line listing the best questions, separated by commas.
   A question is considered the best if the highest number of students answered it correctly.
8. A separate line with the exam result summary.
   The exam is considered successful if more than `85` % of students pass.

Input

| examiners.txt |
| ------------- |
| Stepan M  Darya F   Mikhail M |

| students.txt |
| ------------ |
| Petr M Sergey M Varvara F      Ivan M   Ekaterina F Alexandra F Aleksey M |

| questions.txt |
| ------------- |
| There is a table   A man is a dog’s friend   Solar eclipses affect people   Programming is an interesting activity |

Output

During exam

```table
+------------+----------+
| Student    |  Status  |
+------------+----------+
| Aleksey    | In queue |
| Petr       |  Passed  |
| Ivan       |  Passed  |
| Ekaterina  |  Passed  |
| Sergey     |  Failed  |
| Varvara    |  Failed  |
| Alexandra  |  Failed  |
+------------+----------+

+-------------+-----------------+-----------------+---------+--------------+
| Examiner    | Current student | Total students  | Failed  | Work time    |
+-------------+-----------------+-----------------+---------+--------------+
| Stepan      | Aleksey         |        1        |    0    |    12.31     |
| Darya       | -               |        3        |    2    |    12.14     |
| Mikhail     | -               |        2        |    1    |     7.21     |
+-------------+-----------------+-----------------+---------+--------------+

Remaining in queue: 1 out of 7
Time since exam started: 12.31
```

After exam

```table
+------------+----------+
| Student    |  Status  |
+------------+----------+
| Petr       |  Passed  |
| Ivan       |  Passed  |
| Ekaterina  |  Passed  |
| Sergey     |  Failed  |
| Varvara    |  Failed  |
| Alexandra  |  Failed  |
| Aleksey    |  Failed  |
+------------+----------+

+-------------+-----------------+---------+--------------+
| Examiner    | Total students  | Failed  | Work time    |
+-------------+-----------------+---------+--------------+
| Stepan      |        2        |    1    |    12.35     |
| Darya       |        3        |    2    |    12.14     |
| Mikhail     |        2        |    1    |     7.21     |
+-------------+-----------------+---------+--------------+

Time from exam start to finish: 12.35  
Top-performing students: Ivan  
Top examiners: Stepan, Mikhail  
Students to be expelled: Varvara  
Best questions: There is a table, A man is a dog’s friend  
Result: Exam failed
```

### Exercise 02: Image downloader

Write a link handler that prompts the user to enter an image *URL* and downloads the image asynchronously.
Ask the user for the next *URL* after they enter the previous one.
Continue doing so until they enter an empty line.
If not images have been downloaded by that point, display a message and wait for downloads to finish before terminating the program.
Do not terminate the program if any error occurs.
Store the status for summary output at the end.
The user must specify where to save the downloaded images.
If the specified path is invalid or the program does not have write access, prompt the user to enter a another path.
Before exiting, display a summary of successful and failed downloads.

Input

```urls
./img
https://images2.pics4learning.com/catalog/s/swamp_15.jpg
https://bad-link-no-website-here.strange/img.png
https://images2.pics4learning.com/catalog/p/parrot.jpg
```

Output

Summary of successful and unsuccessful downloads

```table
+----------------------------------------------------------+--------+
| Link                                                     | Status |
+----------------------------------------------------------+--------+
| https://images2.pics4learning.com/catalog/s/swamp_15.jpg | Success|
| https://bad-link-no-website-here.strange/img.png         | Error  |
| https://images2.pics4learning.com/catalog/p/parrot.jpg   | Success|
+----------------------------------------------------------+--------+
```
