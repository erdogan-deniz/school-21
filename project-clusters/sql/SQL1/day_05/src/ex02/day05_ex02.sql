-- Явное отключение линейного поиска:
SET enable_seqscan TO OFF;

CREATE INDEX idx_person_name
ON person UPPER(name);

-- Вывод информации об запросе:
EXPLAIN ANALYZE
SELECT person.name AS name
FROM person;
