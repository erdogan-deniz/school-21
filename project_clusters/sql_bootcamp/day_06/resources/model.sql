CREATE TABLE person (
    id BIGINT PRIMARY KEY,
    name VARCHAR NOT NULL,
    age INTEGER NOT NULL DEFAULT 10,
    gender VARCHAR DEFAULT 'female' NOT NULL,
    address VARCHAR
);

ALTER TABLE person
ADD CONSTRAINT ch_gender CHECK (gender IN ('female', 'male'));

INSERT INTO person VALUES (1, 'Anna', 16, 'female', 'Moscow');
INSERT INTO person VALUES (2, 'Andrey', 21, 'male', 'Moscow');
INSERT INTO person VALUES (3, 'Kate', 33, 'female', 'Kazan');
INSERT INTO person VALUES (4, 'Denis', 13, 'male', 'Kazan');
INSERT INTO person VALUES (5, 'Elvira', 45, 'female', 'Kazan');
INSERT INTO person VALUES (6, 'Irina', 21, 'female', 'Saint-Petersburg');
INSERT INTO person VALUES (7, 'Peter', 24, 'male', 'Saint-Petersburg');
INSERT INTO person VALUES (8, 'Nataly', 30, 'female', 'Novosibirsk');
INSERT INTO person VALUES (9, 'Dmitriy', 18, 'male', 'Samara');

CREATE TABLE pizzeria (
    id BIGINT PRIMARY KEY,
    name VARCHAR NOT NULL,
    rating NUMERIC NOT NULL DEFAULT 0
);

ALTER TABLE pizzeria
ADD CONSTRAINT ch_rating CHECK (rating BETWEEN 0 AND 5);

INSERT INTO pizzeria VALUES (1, 'Pizza Hut', 4.6);
INSERT INTO pizzeria VALUES (2, 'Dominos', 4.3);
INSERT INTO pizzeria VALUES (3, 'DoDo Pizza', 3.2);
INSERT INTO pizzeria VALUES (4, 'Papa Johns', 4.9);
INSERT INTO pizzeria VALUES (5, 'Best Pizza', 2.3);
INSERT INTO pizzeria VALUES (6, 'DinoPizza', 4.2);

CREATE TABLE person_visits (
    id BIGINT PRIMARY KEY,
    person_id BIGINT NOT NULL,
    pizzeria_id BIGINT NOT NULL,
    visit_date DATE NOT NULL DEFAULT CURRENT_DATE,
    CONSTRAINT uk_person_visits UNIQUE (person_id, pizzeria_id, visit_date),
    CONSTRAINT fk_person_visits_person_id FOREIGN KEY (person_id) REFERENCES person (id),
    CONSTRAINT fk_person_visits_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria (id)
);

INSERT INTO person_visits VALUES (1, 1, 1, '2022-01-01');
INSERT INTO person_visits VALUES (2, 2, 2, '2022-01-01');
INSERT INTO person_visits VALUES (3, 2, 1, '2022-01-02');
INSERT INTO person_visits VALUES (4, 3, 5, '2022-01-03');
INSERT INTO person_visits VALUES (5, 3, 6, '2022-01-04');
INSERT INTO person_visits VALUES (6, 4, 5, '2022-01-07');
INSERT INTO person_visits VALUES (7, 4, 6, '2022-01-08');
INSERT INTO person_visits VALUES (8, 5, 2, '2022-01-08');
INSERT INTO person_visits VALUES (9, 5, 6, '2022-01-09');
INSERT INTO person_visits VALUES (10, 6, 2, '2022-01-09');
INSERT INTO person_visits VALUES (11, 6, 4, '2022-01-01');
INSERT INTO person_visits VALUES (12, 7, 1, '2022-01-03');
INSERT INTO person_visits VALUES (13, 7, 2, '2022-01-05');
INSERT INTO person_visits VALUES (14, 8, 1, '2022-01-05');
INSERT INTO person_visits VALUES (15, 8, 2, '2022-01-06');
INSERT INTO person_visits VALUES (16, 8, 4, '2022-01-07');
INSERT INTO person_visits VALUES (17, 9, 4, '2022-01-08');
INSERT INTO person_visits VALUES (18, 9, 5, '2022-01-09');
INSERT INTO person_visits VALUES (19, 9, 6, '2022-01-10');

CREATE TABLE menu (
    id BIGINT PRIMARY KEY,
    pizzeria_id BIGINT NOT NULL,
    pizza_name VARCHAR NOT NULL,
    price NUMERIC NOT NULL DEFAULT 1,
    CONSTRAINT fk_menu_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria (id)
);

INSERT INTO menu VALUES (1, 1, 'cheese pizza', 900);
INSERT INTO menu VALUES (2, 1, 'pepperoni pizza', 1200);
INSERT INTO menu VALUES (3, 1, 'sausage pizza', 1200);
INSERT INTO menu VALUES (4, 1, 'supreme pizza', 1200);
INSERT INTO menu VALUES (5, 6, 'cheese pizza', 950);
INSERT INTO menu VALUES (6, 6, 'pepperoni pizza', 800);
INSERT INTO menu VALUES (7, 6, 'sausage pizza', 1000);
INSERT INTO menu VALUES (8, 2, 'cheese pizza', 800);
INSERT INTO menu VALUES (9, 2, 'mushroom pizza', 1100);
INSERT INTO menu VALUES (10, 3, 'cheese pizza', 780);
INSERT INTO menu VALUES (11, 3, 'supreme pizza', 850);
INSERT INTO menu VALUES (12, 4, 'cheese pizza', 700);
INSERT INTO menu VALUES (13, 4, 'mushroom pizza', 950);
INSERT INTO menu VALUES (14, 4, 'pepperoni pizza', 1000);
INSERT INTO menu VALUES (15, 4, 'sausage pizza', 950);
INSERT INTO menu VALUES (16, 5, 'cheese pizza', 700);
INSERT INTO menu VALUES (17, 5, 'pepperoni pizza', 800);
INSERT INTO menu VALUES (18, 5, 'supreme pizza', 850);

CREATE TABLE person_order (
    id BIGINT PRIMARY KEY,
    person_id BIGINT NOT NULL,
    menu_id BIGINT NOT NULL,
    order_date DATE NOT NULL DEFAULT CURRENT_DATE,
    CONSTRAINT fk_order_person_id FOREIGN KEY (person_id) REFERENCES person (id),
    CONSTRAINT fk_order_menu_id FOREIGN KEY (menu_id) REFERENCES menu (id)
);

INSERT INTO person_order VALUES (1, 1, 1, '2022-01-01');
INSERT INTO person_order VALUES (2, 1, 2, '2022-01-01');
INSERT INTO person_order VALUES (3, 2, 8, '2022-01-01');
INSERT INTO person_order VALUES (4, 2, 9, '2022-01-01');
INSERT INTO person_order VALUES (5, 3, 16, '2022-01-04');
INSERT INTO person_order VALUES (6, 4, 16, '2022-01-07');
INSERT INTO person_order VALUES (7, 4, 17, '2022-01-07');
INSERT INTO person_order VALUES (8, 4, 18, '2022-01-07');
INSERT INTO person_order VALUES (9, 4, 6, '2022-01-08');
INSERT INTO person_order VALUES (10, 4, 7, '2022-01-08');
INSERT INTO person_order VALUES (11, 5, 6, '2022-01-09');
INSERT INTO person_order VALUES (12, 5, 7, '2022-01-09');
INSERT INTO person_order VALUES (13, 6, 13, '2022-01-01');
INSERT INTO person_order VALUES (14, 7, 3, '2022-01-03');
INSERT INTO person_order VALUES (15, 7, 9, '2022-01-05');
INSERT INTO person_order VALUES (16, 7, 4, '2022-01-05');
INSERT INTO person_order VALUES (17, 8, 8, '2022-01-06');
INSERT INTO person_order VALUES (18, 8, 14, '2022-01-07');
INSERT INTO person_order VALUES (19, 9, 18, '2022-01-09');
INSERT INTO person_order VALUES (20, 9, 6, '2022-01-10');
