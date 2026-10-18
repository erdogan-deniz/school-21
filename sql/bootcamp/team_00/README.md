# Team 00 - Piscine SQL

## _Traveling Salesman Problem_

Resume: Today you will implementing a quick solution on SQL to achieve results of Traveling Salesman Problem.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Preamble](#preamble)
2. [Chapter II](#chapter-ii) \
    2.1. [General Rules](#general-rules)
3. [Chapter III](#chapter-iii) \
    3.1. [Rules of the day](#rules-of-the-day)  
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00 - Classical TSP](#exercise-00---classical-tsp)  
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01 - Opposite TSP](#exercise-01---opposite-tsp)  

## Chapter I

## Preamble

![T00_01](misc/images/T00_01.png)

Given a finite number of "cities" and the cost of travel between each pair of cities, find the cheapest way to visit all the cities and return to your starting point. (In the picture, the Proctor and Gamble company held a contest in 1962.  The contest required solving a TSP for a given set of 33 cities.  There was a tie between many people who found the optimum.  An early TSP researcher, Professor Gerald Thompson of Carnegie Mellon University, was one of the winners).

The travel costs are symmetric in the sense that traveling from city X to city Y costs as much as traveling from Y to X; the "way to visit all the cities" is simply the order in which the cities are visited. In other words, the data consists of integer weights assigned to the edges of a finite complete graph; the goal is to find a Hamiltonian cycle (i.e., a cycle that passes through all vertices) with the minimum total weight.  In this context, Hamiltonian cycles are commonly called tours.

![T00_00](misc/images/T00_00.png)

The origins of the TSP are unclear. In the 1920s, the mathematician and economist Karl Menger published it among his colleagues in Vienna. In the 1930s, the problem resurfaced in mathematical circles in Princeton. In the 1940s, it was studied by statisticians (Mahalanobis (1940), Jessen (1942), Gosh (1948), Marks (1948)) in connection with an agricultural application, and the mathematician Merill Flood popularized it among his colleagues at the RAND Corporation.  Eventually, the TSP became known as the prototype of a hard problem in combinatorial optimization: examining the tours one by one is out of the question due to their large number, and for a long time there was no other idea on the horizon.

## Chapter II

## General Rules

- Use this page as your only reference. Do not listen to rumors and speculations about how to prepare your solution.
- Make sure you are using the latest version of PostgreSQL.
- It is perfectly fine if you use the IDE to write source code (aka SQL script).
- To be evaluated, your solution must be in your GIT repository.
- Your solutions will be evaluated by your peers.
- You should not leave any files in your directory other than those explicitly specified by the exercise instructions. It is recommended that you modify your `.gitignore` to avoid accidents.
- Got a question? Ask your neighbor to the right. Otherwise, try your neighbor on the left.
- Your reference manual: mates / Internet / Google.
- Read the examples carefully. You may need things not specified in the topic.
- And may the SQL-Force be with you!
Absolutely anything can be represented in SQL! Let's get started and have fun!

## Chapter III

## Rules of the day

- Please make sure you have your own database and access for it on your PostgreSQL cluster.
- All tasks contain a list of Allowed and Denied sections with listed database options, database types, SQL constructions etc. Please have a look at this section before you start.

## Chapter IV

## Exercise 00 - Classical TSP

| Exercise 00: Classical TSP|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex00                                                                                                                     |
| Files to turn-in                      | `team00_ex00.sql` DDL for table creation with INSERTs of data; SQL DML statement                                                                                |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL|
| SQL Syntax Pattern                        | Recursive Query|

![T00_02](misc/images/T00_02.png)

Take a look at the Graph on the left.
There are 4 cities (a, b, c and d) and arcs between them with costs (or taxes). Actually, the cost is (a,b) = (b,a).

Please create a table with named nodes using structure {point1, point2, cost} and fill data based on a picture (remember there are direct and reverse paths between 2 nodes).
Please write a SQL statement that returns all tours (aka paths) with minimum travel cost if we start from city "a".
Remember, you need to find the cheapest way to visit all cities and return to your starting point. For example, the tour looks like a -> b -> c -> d -> a.

Below is an example of the output data. Please sort the data by total_cost and then by tour.

| total_cost | tour |
| ------ | ------ |
| 80 | {a,b,d,c,a} |
| ... | ... |

## Chapter V

## Exercise 01 - Opposite TSP

| Exercise 01: Opposite TSP|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex01                                                                                                                     |
| Files to turn-in                      | `team00_ex01.sql`     SQL DML statement                                                                             |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL|
| SQL Syntax Pattern                        | Recursive Query|

Please add a way to see additional rows with the most expensive cost to the SQL from the previous exercise. Take a look at the sample data below. Please sort the data by total_cost and then by trip.

| total_cost | tour |
| ------ | ------ |
| 80 | {a,b,d,c,a} |
| ... | ... |
| 95 | {a,d,c,b,a} |
