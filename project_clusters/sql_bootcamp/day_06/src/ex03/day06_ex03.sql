CREATE UNIQUE INDEX idx_person_discounts_unique ON person_discounts (person_id, pizzeria_id);

-- Is used as an explicitly disabling of a linear search.
SET enable_seqscan TO OFF;

-- An "EXPLAIN ANALYZE" is used to display detailed information about the operation.
EXPLAIN ANALYZE
SELECT
    person_discounts.person_id AS person_id,
    person_discounts.pizzeria_id AS pizzeria_id
FROM
    person_discounts;
