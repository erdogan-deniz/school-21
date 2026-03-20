UPDATE
    menu
SET
    price = (
        SELECT
            price AS price
        FROM
            menu
        WHERE
            (menu.pizza_name = 'greek pizza')
    ) * 0.9
WHERE
    menu.pizza_name = 'greek pizza';
