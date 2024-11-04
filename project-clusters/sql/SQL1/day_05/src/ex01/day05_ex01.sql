-- Явное отключение линейного поиска:
SET enable_seqscan TO OFF;

-- Вывод информации об запросе:
EXPLAIN ANALYZE
SELECT
	  menu.pizza_name AS pizza_name,
	  pizzeria.name AS pizzeria_name
FROM menu
JOIN pizzeria
ON (pizzeria.id = menu.pizzeria_id);
