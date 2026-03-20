-- Explicitly disabling linear search
SET
    enable_seqscan TO OFF;

-- Deleting an unnecessary index
-- DROP INDEX idx_1;
-- Creating an index

-- CREATE UNIQUE INDEX idx_1
-- ON pizzeria (rating);
-- Output of information about the request

EXPLAIN
ANALYZE
SELECT
    m.pizza_name AS pizza_name,
    max(rating) OVER (
        PARTITION BY rating -- By rating, we divide into groups
        ORDER BY
            rating -- Sorts all entries by rating
            ROWS BETWEEN UNBOUNDED PRECEDING
            AND UNBOUNDED FOLLOWING -- We take into account all the lines
    ) AS k
FROM
    menu m
    INNER JOIN pizzeria pz ON (m.pizzeria_id = pz.id)
ORDER BY
    1,
    2;
