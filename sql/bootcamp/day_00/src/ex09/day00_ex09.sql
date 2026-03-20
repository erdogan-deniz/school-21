SELECT
    (
        SELECT
            name
        FROM
            person
        WHERE
            (id = person_id)
    ) AS person_name,
    (
        SELECT
            name
        FROM
            pizzeria
        WHERE
            (id = pizzeria_id)
    ) AS pizzeria_name
FROM
    (
        SELECT
            person_id,
            pizzeria_id
        FROM
            person_visits
        WHERE
            (visit_date BETWEEN '2022-01-07' AND '2022-01-09')
    ) AS pv
ORDER BY
    person_name ASC,
    pizzeria_name DESC;
