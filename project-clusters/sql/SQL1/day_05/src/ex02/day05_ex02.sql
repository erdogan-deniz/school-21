-- Explicitly disabling linear search
SET
    enable_seqscan TO OFF;

CREATE INDEX
    idx_person_name ON person UPPER(name);

-- Output of information about the request
EXPLAIN
ANALYZE
SELECT
    person.name AS name
FROM
    person;
