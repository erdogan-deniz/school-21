SELECT
    person.name AS person_name,
    pizza_name,
    pizzeria.name AS pizzeria_name
FROM
    person
    INNER JOIN person_order ON (person.id = person_order.person_id)
    INNER JOIN menu ON (person_order.menu_id = menu.id)
    INNER JOIN pizzeria ON (menu.pizzeria_id = pizzeria.id)
ORDER BY
    person_name,
    pizza_name,
    pizzeria_name
