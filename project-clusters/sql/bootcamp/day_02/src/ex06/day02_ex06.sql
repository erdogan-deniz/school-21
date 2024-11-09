SELECT
    menu.pizza_name AS pizza_name,
    pizzeria.name AS pizzeria_name
FROM
    pizzeria
    JOIN menu ON (pizzeria.id = menu.pizzeria_id)
    JOIN person_order ON (menu.id = person_order.menu_id)
    JOIN person ON (person.id = person_order.person_id)
WHERE
    (person.name = 'Denis')
    OR (person.name = 'Anna')
ORDER BY
    pizza_name,
    pizzeria_name;
