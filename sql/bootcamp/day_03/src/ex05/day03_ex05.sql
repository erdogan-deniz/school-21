SELECT
    pizzeria.name AS pizzeria_name
FROM
    pizzeria
WHERE
    pizzeria.id IN (
        (
            SELECT
                person_visits.pizzeria_id
            FROM
                pizzeria
                JOIN person_visits ON (person_visits.pizzeria_id = pizzeria.id)
                JOIN person ON (person.id = person_visits.person_id)
                JOIN person_order ON (person_order.person_id = person.id)
            WHERE
                (person.name = 'Andrey')
        )
        EXCEPT
        (
            SELECT
                pizzeria_id
            FROM
                menu
                JOIN pizzeria ON (pizzeria.id = menu.pizzeria_id)
                JOIN person_order ON (person_order.menu_id = menu.id)
                JOIN person ON (person_order.person_id = person.id)
            WHERE
                (person.name = 'Andrey')
        )
    )
ORDER BY
    pizzeria_name;
