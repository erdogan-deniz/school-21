CREATE TABLE person (
    id BIGINT PRIMARY KEY,
    name VARCHAR NOT NULL,
    age INTEGER NOT NULL DEFAULT 10,
    gender VARCHAR NOT NULL DEFAULT 'female',
    address VARCHAR
);

ALTER TABLE person
ADD CONSTRAINT ch_gender CHECK (gender IN ('female', 'male'));

INSERT INTO person VALUES
    (1, 'Anna', 16, 'female', 'Moscow'),
    (2, 'Andrey', 21, 'male', 'Moscow'),
    (3, 'Kate', 33, 'female', 'Kazan'),
    (4, 'Denis', 13, 'male', 'Kazan'),
    (5, 'Elvira', 45, 'female', 'Kazan'),
    (6, 'Irina', 21, 'female', 'Saint-Petersburg'),
    (7, 'Peter', 24, 'male', 'Saint-Petersburg'),
    (8, 'Nataly', 30, 'female', 'Novosibirsk'),
    (9, 'Dmitriy', 18, 'male', 'Samara');

CREATE TABLE pizzeria (
    id BIGINT PRIMARY KEY,
    name VARCHAR NOT NULL,
    rating NUMERIC NOT NULL DEFAULT 0
);

ALTER TABLE pizzeria
ADD CONSTRAINT ch_rating CHECK (rating BETWEEN 0 AND 5);

INSERT INTO pizzeria VALUES
    (1, 'Pizza Hut', 4.6),
    (2, 'Dominos', 4.3),
    (3, 'DoDo Pizza', 3.2),
    (4, 'Papa Johns', 4.9),
    (5, 'Best Pizza', 2.3),
    (6, 'DinoPizza', 4.2);

CREATE TABLE person_visits (
    id BIGINT PRIMARY KEY,
    person_id BIGINT NOT NULL,
    pizzeria_id BIGINT NOT NULL,
    visit_date DATE NOT NULL DEFAULT CURRENT_DATE,
    CONSTRAINT uk_person_visits UNIQUE (person_id, pizzeria_id, visit_date),
    CONSTRAINT fk_person_visits_person_id FOREIGN KEY (person_id) REFERENCES person(id),
    CONSTRAINT fk_person_visits_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria(id)
);

INSERT INTO person_visits VALUES
    (1, 1, 1, '2022-01-01'),
    (2, 2, 2, '2022-01-01'),
    (3, 2, 1, '2022-01-02'),
    (4, 3, 5, '2022-01-03'),
    (5, 3, 6, '2022-01-04'),
    (6, 4, 5, '2022-01-07'),
    (7, 4, 6, '2022-01-08'),
    (8, 5, 2, '2022-01-08'),
    (9, 5, 6, '2022-01-09'),
    (10, 6, 2, '2022-01-09'),
    (11, 6, 4, '2022-01-01'),
    (12, 7, 1, '2022-01-03'),
    (13, 7, 2, '2022-01-05'),
    (14, 8, 1, '2022-01-05'),
    (15, 8, 2, '2022-01-06'),
    (16, 8, 4, '2022-01-07'),
    (17, 9, 4, '2022-01-08'),
    (18, 9, 5,'2022-01-09'),
    (19, 9, 6,'2022-01-10');

CREATE TABLE menu (
    id BIGINT PRIMARY KEY,
    pizzeria_id BIGINT NOT NULL,
    pizza_name VARCHAR NOT NULL,
    price NUMERIC NOT NULL DEFAULT 1,
    CONSTRAINT fk_menu_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria(id)
);

INSERT INTO menu VALUES
    (1, 1,'cheese pizza',900),
    (2 ,1,'pepperoni pizza',1200),
    (3 ,1,'sausage pizza',1200),
    (4 ,1,'supreme pizza',1200),
    (5 ,6,'cheese pizza',950),
    (6 ,6,'pepperoni pizza',800),
    (7 ,6,'sausage pizza',1000),
    (8 ,2,'cheese pizza',800),
    (9 ,2,'mushroom pizza',1100),
    (10 ,3,'cheese pizza',780),
    (11 ,3,'supreme pizza',850),
    (12 ,4,'cheese pizza',700),
    (13 ,4,'mushroom pizza',950),
    (14 ,4,'pepperoni pizza',1000),
    (15 ,4,'sausage pizza',950),
    (16 ,5,'cheese pizza',700),
    (17 ,5,'pepperoni pizza',800),
    (18 ,5,'supreme pizza',850);

CREATE TABLE person_order (
   id BIGINT PRIMARY KEY,
   person_id BIGINT NOT NULL,
   menu_id BIGINT NOT NULL,
   order_date DATE NOT NULL DEFAULT CURRENT_DATE,
   CONSTRAINT fk_order_person_id FOREIGN KEY(person_id) REFERENCES person(id),
   CONSTRAINT fk_order_menu_id FOREIGN KEY(menu_id) REFERENCES menu(id)
);

INSERT INTO person_order VALUES
   (1 ,1 ,1 ,'2022-01-01'),
   (2 ,1 ,2 ,'2022-01-01'),
   (3 ,2 ,8 ,'2022-01-01'),
   (4 ,2 ,9 ,'2022-01-01'),
   (5 ,3 ,16 ,'2022-01-04'),
   (6 ,4 ,16 ,'2022-01-07'),
   (7 ,4 ,17 ,'2022-01-07'),
   (8 ,4 ,18 ,'2022-01-07'),
   (9 ,4 ,6 ,'2022-01-08'),
   (10 ,4 ,7 ,'2022-01-08'),
   (11 ,5 ,6 ,'2022-01-09'),
   (12 ,5 ,7 ,'2022-01-09'),
   (13 ,6 ,13 ,'2022-01-01'),
   (14 ,7 ,3 ,'2022-01-03'),
   (15 ,7 ,9 ,'2022-01-05'),
   (16 ,7 ,4 ,'2022-01-05'),
   (17 ,8 ,8 ,'2022-01-06'),
   (18 ,8 ,14 ,'2022-01-07'),
   (19 ,9 ,18 ,'2022-01-09'),
   (20 ,9 ,6 ,'2022 -01 -10');
