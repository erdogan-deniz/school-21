-- Явное отключение линейного поиска:
SET enable_seqscan TO OFF;

CREATE UNIQUE INDEX idx_person_order_order_date
ON person_order (person_id , menu_id) 
WHERE (order_date = '2022-01-01');

-- Вывод информации об запросе:
EXPLAIN ANALYZE
SELECT
	  person_order.person_id AS person_id,
	  person_order.menu_id AS menu_id
FROM person_order
WHERE (order_date = '2022-01-01');
