-- Explicitly disabling linear search
SET
    enable_seqscan TO OFF;

CREATE UNIQUE INDEX idx_menu_unique ON menu (pizzeria_id, pizza_name);

-- Output of information about the request
EXPLAIN
ANALYZE
SELECT
    menu.pizzeria_id AS pizzeria_id,
    menu.pizza_name AS pizza_name
FROM
    menu;
