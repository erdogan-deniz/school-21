INSERT INTO
    person_visits (id, person_id, pizzeria_id, visit_date)
VALUES
    (
        (
            SELECT
                MAX(person_visits.id) + 1 AS new_id
            FROM
                person_visits
        ),
        (
            SELECT
                person.id AS person_id
            FROM
                person
            WHERE
                person.name = 'Denis'
        ),
        (
            SELECT
                pizzeria.id AS pizz_id
            FROM
                pizzeria
            WHERE
                pizzeria.name = 'Dominos'
        ),
        '2022-02-24'
    );

INSERT INTO
    person_visits (id, person_id, pizzeria_id, visit_date)
VALUES
    (
        (
            SELECT
                MAX(person_visits.id) + 1 AS new_id
            FROM
                person_visits
        ),
        (
            SELECT
                person.id AS person_id
            FROM
                person
            WHERE
                person.name = 'Irina'
        ),
        (
            SELECT
                pizzeria.id AS pizz_id
            FROM
                pizzeria
            WHERE
                pizzeria.name = 'Dominos'
        ),
        '2022-02-24'
    );
