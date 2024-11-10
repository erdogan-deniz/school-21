SELECT
    name
FROM
    pizzeria
WHERE
    (
        pizzeria.id NOT IN (
            SELECT
                pizzeria_id
            FROM
                person_visits
        )
    )
SELECT
    name
FROM
    pizzeria
WHERE
    NOT EXISTS (
        SELECT
            *
        FROM
            person_visits
        WHERE
            (pizzeria_id = pizzeria.id)
    )
