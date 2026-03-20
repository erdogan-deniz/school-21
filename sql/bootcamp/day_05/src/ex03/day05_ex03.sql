-- Explicitly disabling linear search
SET
    enable_seqscan TO OFF;

CREATE INDEX
    idx_person_order_multi ON person_order (person_id) INCLUDE (menu_id, order_date);

-- Output of information about the request
EXPLAIN
ANALYZE
SELECT
    person_order.person_id AS person_id,
    person_order.menu_id AS menu_id,
    person_order.order_date AS order_date
FROM
    person_order
WHERE
    (person_id = 8)
    AND (menu_id = 19);
