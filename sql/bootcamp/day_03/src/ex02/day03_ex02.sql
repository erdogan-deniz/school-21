SELECT
    menu.pizza_name AS pizza_name,
    menu.price AS price,
    pizzeria.name AS pizzeria_name
FROM
    menu
    JOIN pizzeria ON (pizzeria.id = menu.pizzeria_id)
WHERE
    menu.id IN (
        SELECT
            menu.id
        FROM
            menu
        EXCEPT
        SELECT
            person_order.menu_id
        FROM
            person_order
    )
ORDER BY
    pizza_name,
    price;
