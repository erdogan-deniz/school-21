-- Explicitly disabling linear search
SET
    enable_seqscan TO OFF;

-- Output of information about the request
EXPLAIN
ANALYZE
SELECT
    menu.pizza_name AS pizza_name,
    pizzeria.name AS pizzeria_name
FROM
    menu
    JOIN pizzeria ON (pizzeria.id = menu.pizzeria_id);
