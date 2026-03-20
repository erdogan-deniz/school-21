INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT
    -- The default "ROW_NUMBER() OVER()" returns a sequence of 1s.
    (
        ROW_NUMBER() OVER () + (
            SELECT
                -- A "COALESCE()" returns the first non-null value; it calculates once.
                COALESCE(MAX(person_discounts.id), 0)
            FROM
                person_discounts
        )
    ) AS id,
    person_order.person_id AS person_id,
    menu.pizzeria_id AS pizzeria_id,
    CASE
        -- A count of grouped lines.
        WHEN COUNT(*) = 1 THEN 10.5
        WHEN COUNT(*) = 2 THEN 22
        ELSE 30
    END AS discount
FROM
    person_order  -- Use an "INNER JOIN" to dismiss null fields.
    INNER JOIN menu ON person_order.menu_id = menu.id
GROUP BY
    person_order.person_id,
    menu.pizzeria_id;
