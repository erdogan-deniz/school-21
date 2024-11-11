SELECT
    person.name AS name,
    menu.pizza_name AS pizza_name,
    menu.price AS price,
    -- A "ROUND()" is used to get a defined precision.
    -- If we get a "NULL" value from the "menu.price", the result field will be "NULL" too.
    -- The ":: integer" is used as an explicit type conversion.
    ROUND(
        menu.price * COALESCE(1 - person_discounts.discount / 100, 1)
    ) :: integer AS discount_price,
    pizzeria.name AS pizzeria_name
FROM
    person_order
    INNER JOIN person ON person.id = person_order.person_id
    INNER JOIN menu ON menu.id = person_order.menu_id
    INNER JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
    INNER JOIN person_discounts ON person_discounts.person_id = person_order.person_id
ORDER BY
    person.name,
    menu.pizza_name;
