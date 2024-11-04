# Day 03 - Piscine SQL

## _Continuing to JOIN and make change in data_

Resume: Today you will see how to change data based on DML language.

## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Preamble](#preamble)
2. [Chapter II](#chapter-ii) \
    2.1. [General Rules](#general-rules)
3. [Chapter III](#chapter-iii) \
    3.1. [Rules of the day](#rules-of-the-day)  
4. [Chapter IV](#chapter-iv) \
    4.1. [Exercise 00 - Let’s find appropriate prices for Kate](#exercise-00-lets-find-appropriate-prices-for-kate)  
5. [Chapter V](#chapter-v) \
    5.1. [Exercise 01 - Let’s find forgotten menus](#exercise-01-lets-find-forgotten-menus)  
6. [Chapter VI](#chapter-vi) \
    6.1. [Exercise 02 - Let’s find forgotten pizza and pizzerias](#exercise-02-lets-find-forgotten-pizza-and-pizzerias)  
7. [Chapter VII](#chapter-vii) \
    7.1. [Exercise 03 - Let’s compare visits](#exercise-03-lets-compare-visits)  
8. [Chapter VIII](#chapter-viii) \
    8.1. [Exercise 04 - Let’s compare orders](#exercise-04-lets-compare-orders)
9. [Chapter IX](#chapter-ix) \
    9.1. [Exercise 05 - Visited but did not make any order](#exercise-05-visited-but-did-not-make-any-order)
10. [Chapter X](#chapter-x) \
    10.1. [Exercise 06 - Find price-similarity pizzas](#exercise-06-find-price-similarity-pizzas)
11. [Chapter XI](#chapter-xi) \
    11.1. [Exercise 07 - Let’s cook a new type of pizza](#exercise-07-lets-cook-a-new-type-of-pizza)
12. [Chapter XII](#chapter-xii) \
    12.1. [Exercise 08 - Let’s cook a new type of pizza with more dynamics](#exercise-08-lets-cook-a-new-type-of-pizza-with-more-dynamics)
13. [Chapter XIII](#chapter-xiii) \
    13.1. [Exercise 09 - New pizza means new visits](#exercise-09-new-pizza-means-new-visits)
14. [Chapter XIV](#chapter-xiv) \
    14.1. [Exercise 10 - New visits means new orders](#exercise-10-new-visits-means-new-orders)
15. [Chapter XV](#chapter-xv) \
    15.1. [Exercise 11 - “Improve” a price for clients](#exercise-11-improve-a-price-for-clients)    
16. [Chapter XVI](#chapter-xvi) \
    16.1. [Exercise 12 - New orders are coming!](#exercise-12-new-orders-are-coming)
17. [Chapter XVII](#chapter-xvii) \
    17.1. [Exercise 13 - Money back to our customers](#exercise-13-money-back-to-our-customers)

## Chapter I
## Preamble

![D03_01](misc/images/D03_01.png)

Relation Theory is a mathematical foundation for modern Relational Databases. EEvery aspect of databases has a corresponding mathematical and logical justification. Including INSERT / UPDATE / DELETE operators. (Dr. Edgar Frank Codd is in the picture).

How the INSERT operator works from a mathematical point of view.

|  |  |
| ------ | ------ |
|`INSERT rel RELATION {TUPLE {A INTEGER(4),B INTEGER(4),C STRING ('Hello') }};` | You can use mathematical INSERT statements and integrate “tuple” construction to convert an incoming data to row. |
| From the other side, you can use explicit assignment with the UNION operator. | `rel:=rel UNION RELATION {TUPLE {A INTEGER(4), B INTEGER (7), C STRING ('Hello')}};` |

What’s about the DELETE statement?

|  |  |
| ------ | ------ |
|`DELETE rel WHERE A = 1;` | If you want to delete a row for A = 1, you can do it in a direct way. |
| ... or by using a new assignment without key A = 1 | `rel:=rel WHERE NOT (A = 1);` |

... and finally UPDATE statement. Also there are 2 cases.

|  |  |
| ------ | ------ |
|`UPDATE rel WHERE A = 1 {B:= 23*A, C:='String #4'};` | Update statement from mathematical point of view |
| New assignment for relation variable rel based on CTE and working with Sets | `rel:=WITH (rel WHERE A = 1) AS T1, (EXTEND T1 ADD (23*A AS NEW_B, 'String #4' AS NEW_C)) AS T2, T2 {ALL BUT B,C} AS T3, (T3 RENAME (NEW _B AS B, NEW _C AS C)) AS T4: (S MINUS T1) UNION T4;` |

The last case with UPDATE statement is really interesting, because in other words you add a new tuple and after that make a MINUS of the old row. Same behavior in the physical implementation! Actually, `UPDATE = DELETE + INSERT` and there is a special term "Tombstone" status for a particular deleted/updated row. Then if you have a lot of Tombstones then you have a bad TPS metric and you need to control your dead data!

![D03_02](misc/images/D03_02.png)

Let’s make a cheese of our data! :-)


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
- Please download a [script](materials/model.sql) with Database Model here and apply the script to your database (you can use command line with psql or just run it through any IDE, for example DataGrip from JetBrains or pgAdmin from PostgreSQL community). 
- All tasks contain a list of Allowed and Denied sections with listed database options, database types, SQL constructions etc. Please have a look at this section before you start.
- Please take a look at the Logical View of our Database Model. 

![schema](misc/images/schema.png)


1. **pizzeria** table (Dictionary Table with available pizzerias)
- field id - primary key
- field name - name of pizzeria
- field rating - average rating of pizzeria (from 0 to 5 points)
2. **person** table (Dictionary Table with persons who loves pizza)
- field id - primary key
- field name - name of person
- field age - age of person
- field gender - gender of person
- field address - address of person
3. **menu** table (Dictionary Table with available menu and price for concrete pizza)
- field id - primary key
- field pizzeria_id - foreign key to pizzeria
- field pizza_name - name of pizza in pizzeria
- field price - price of concrete pizza
4. **person_visits** table (Operational Table with information about visits of pizzeria)
- field id - primary key
- field person_id - foreign key to person
- field pizzeria_id - foreign key to pizzeria
- field visit_date - date (for example 2022-01-01) of person visit 
5. **person_order** table (Operational Table with information about persons orders)
- field id - primary key
- field person_id - foreign key to person
- field menu_id - foreign key to menu
- field order_date - date (for example 2022-01-01) of person order 

Persons' visit and persons' order are different entities and don't contain any correlation between data. For example, a client can be in one restraunt (just looking at menu) and in this time make an order in different one by phone or by mobile application. Or another case,  just be at home and again make a call with order without any visits.

## Chapter IV
## Exercise 00 - Let’s find appropriate prices for Kate

| Exercise 00: Let’s find appropriate prices for Kate |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex00                                                                                                                     |
| Files to turn-in                      | `day03_ex00.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Please write a SQL statement that returns a list of pizza names, pizza prices, pizzeria names, and visit dates for Kate and for prices ranging from 800 to 1000 rubles. Please sort by pizza, price, and pizzeria name. See a sample of the data below.

| pizza_name | price | pizzeria_name | visit_date |
| ------ | ------ | ------ | ------ |
| cheese pizza | 950 | DinoPizza | 2022-01-04 |
| pepperoni pizza | 800 | Best Pizza | 2022-01-03 |
| pepperoni pizza | 800 | DinoPizza | 2022-01-04 |
| ... | ... | ... | ... |


## Chapter V
## Exercise 01 - Let’s find forgotten menus

| Exercise 01: Let’s find forgotten menus|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex01                                                                                                                     |
| Files to turn-in                      | `day03_ex01.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
| **Denied**                               |                                                                                                                          |
| SQL Syntax Construction                        | any type of `JOINs`                                                                                              |

Find all menu identifiers that are not ordered by anyone. The result should be sorted by identifier. The sample output is shown below.

| menu_id |
| ------ |
| 5 |
| 10 |
| ... |


## Chapter VI
## Exercise 02 - Let’s find forgotten pizza and pizzerias

| Exercise 02: Let’s find forgotten pizza and pizzerias|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex02                                                                                                                     |
| Files to turn-in                      | `day03_ex02.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Please use the SQL statement from Exercise #01 and display the names of pizzas from the pizzeria that no one has ordered, including the corresponding prices. The result should be sorted by pizza name and price. The sample output data is shown below.

| pizza_name | price | pizzeria_name |
| ------ | ------ | ------ |
| cheese pizza | 700 | Papa Johns |
| cheese pizza | 780 | DoDo Pizza |
| ... | ... | ... |

## Chapter VII
## Exercise 03 - Let’s compare visits

| Exercise 03: Let’s compare visits |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex03                                                                                                                     |
| Files to turn-in                      | `day03_ex03.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Please find pizzerias that have been visited more often by women or by men. Save duplicates for any SQL operators with sets (UNION ALL, EXCEPT ALL, INTERSECT ALL constructions). Please sort a result by the name of the pizzeria. The sample data is shown below.


| pizzeria_name | 
| ------ | 
| Best Pizza | 
| Dominos |
| ... |

## Chapter VIII
## Exercise 04 - Let’s compare orders


| Exercise 04: Let’s compare orders |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex04                                                                                                                     |
| Files to turn-in                      | `day03_ex04.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Find a union of pizzerias that have orders from either women or men. In other words, you should find a set of names of pizzerias that have been ordered only by women and make "UNION" operation with set of names of pizzerias that have been ordered only by men. Please be careful with word "only" for both genders. For all SQL operators with sets don't store duplicates (`UNION`, `EXCEPT`, `INTERSECT`).  Please sort a result by the name of the pizzeria. The sample data is shown below.


| pizzeria_name | 
| ------ | 
| Papa Johns | 

## Chapter IX
## Exercise 05 - Visited but did not make any order


| Exercise 05: Visited but did not make any order |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex05                                                                                                                     |
| Files to turn-in                      | `day03_ex05.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Write an SQL statement that returns a list of pizzerias that Andrey visited but did not order from. Please order by the name of the pizzeria. The sample data is shown below.


| pizzeria_name | 
| ------ | 
| Pizza Hut | 



## Chapter X
## Exercise 06 - Find price-similarity pizzas


| Exercise 06: Find price-similarity pizzas |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex06                                                                                                                     |
| Files to turn-in                      | `day03_ex06.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Find the same pizza names that have the same price, but from different pizzerias. Make sure that the result is ordered by pizza name. The data sample is shown below. Please make sure that your column names match the column names below.

| pizza_name | pizzeria_name_1 | pizzeria_name_2 | price |
| ------ | ------ | ------ | ------ |
| cheese pizza | Best Pizza | Papa Johns | 700 |
| ... | ... | ... | ... |

## Chapter XI
## Exercise 07 - Let’s cook a new type of pizza


| Exercise 07: Let’s cook a new type of pizza |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex07                                                                                                                     |
| Files to turn-in                      | `day03_ex07.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |

Please register a new pizza with the name "greek pizza" (use id = 19) with the price of 800 rubles in the restaurant "Dominos" (pizzeria_id = 2).
**Warning**: this exercise is likely to cause the modification of data in the wrong way. Actually, you can restore the original database model with data from the [link](materials/model.sql).


## Chapter XII
## Exercise 08 - Let’s cook a new type of pizza with more dynamics


| Exercise 08: Let’s cook a new type of pizza with more dynamics |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex08                                                                                                                     |
| Files to turn-in                      | `day03_ex08.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |           
| **Denied**                               |                                                                                                                          |
| SQL Syntax Pattern                        | Don’t use direct numbers for identifiers of Primary Key and pizzeria                                                                                               |       

Please register a new pizza with the name "sicilian pizza" (whose id should be calculated by the formula "maximum id value + 1") with the price of 900 rubles in the restaurant "Dominos" (please use internal query to get the identifier of the pizzeria).
**Warning**: This exercise is likely to cause the modification of data in the wrong way. Actually, you can restore the original database model with data from the link in the "Rules of the day" section and replay the script from Exercise 07.


## Chapter XIII
## Exercise 09 - New pizza means new visits


| Exercise 09: New pizza means new visits |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex09                                                                                                                     |
| Files to turn-in                      | `day03_ex09.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
| **Denied**                               |                                                                                                                          |
| SQL Syntax Pattern                        | Don’t use direct numbers for identifiers of Primary Key and pizzeria                                                                                               |       

Please record new visits to Domino's restaurant by Denis and Irina on February 24, 2022.
**Warning**: This exercise is likely to cause the modification of data in the wrong way. Actually, you can restore the original database model with data from the link in the "Rules of the Day" section and replay the script from Exercises 07 and 08.


## Chapter XIV
## Exercise 10 - New visits means new orders


| Exercise 10: New visits means new orders |                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex10                                                                                                                     |
| Files to turn-in                      | `day03_ex10.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
| **Denied**                               |                                                                                                                          |
| SQL Syntax Pattern                        | Don’t use direct numbers for identifiers of Primary Key and pizzeria                                                                                               |     


Please register new orders from Denis and Irina on February 24, 2022 for the new menu with "sicilian pizza".
**Warning**: This exercise will probably cause you to change data in the wrong way. Actually, you can restore the original database model with data from the link in the Rules of the Day section and replay the script from Exercises 07, 08 and 09.


## Chapter XV
## Exercise 11 - “Improve” a price for clients


| Exercise 11: “Improve” a price for clients|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex11                                                                                                                     |
| Files to turn-in                      | `day03_ex11.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
    
Please change the price of "greek pizza" to -10% of the current value.
**Warning**: This exercise is likely to cause you to change data in the wrong way. Actually, you can rebuild the original database model with data from the link in the "Rules of the Day" section and replay the script from Exercises 07, 08, 09, and 10.


## Chapter XVI
## Exercise 12 - New orders are coming!


| Exercise 12: New orders are coming!|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex12                                                                                                                     |
| Files to turn-in                      | `day03_ex12.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
| SQL Syntax Construction                        | `generate_series(...)`                                                                                              |
| SQL Syntax Patten                        | Please use “insert-select” pattern
`INSERT INTO ... SELECT ...`|
| **Denied**                               |                                                                                                                          |
| SQL Syntax Patten                        | - Don’t use direct numbers for identifiers of Primary Key, and menu 
- Don’t use window functions like `ROW_NUMBER( )`
- Don’t use atomic `INSERT` statements |

Please register new orders of all persons for "greek pizza" on February 25, 2022.
**Warning**: This exercise will probably cause you to change data in the wrong way. Actually, you can restore the original database model with data from the link in the "Rules of the Day" section and replay the script from Exercises 07, 08, 09, 10 and 11.


## Chapter XVII
## Exercise 13 - Money back to our customers


| Exercise 13: Money back to our customers|                                                                                                                          |
|---------------------------------------|--------------------------------------------------------------------------------------------------------------------------|
| Turn-in directory                     | ex13                                                                                                                     |
| Files to turn-in                      | `day03_ex13.sql`                                                                                 |
| **Allowed**                               |                                                                                                                          |
| Language                        | ANSI SQL                                                                                              |
    
Write 2 SQL (DML) statements that delete all new orders from Exercise #12 based on the order date. Then delete "greek pizza" from the menu. 
**Warning**: This exercise is likely to cause you to modify data in the wrong way. Actually, you can rebuild the original database model with data from the link in the "Rules of the Day section" and replay the script from Exercises 07, 08, 09, 10, 11, 12, and 13.
