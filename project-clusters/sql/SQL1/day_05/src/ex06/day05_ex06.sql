-- Явное отключение линейного поиска:
SET enable_seqscan TO OFF;

-- Удаление ненужного индекса:
-- DROP INDEX idx_1;

-- CREATE UNIQUE INDEX idx_1
-- ON pizzeria (rating);


-- Вывод информации об запросе:
EXPLAIN ANALYZE
SELECT
	  m.pizza_name AS pizza_name,
	  max(rating) OVER (
		  				PARTITION BY rating  -- По рейтингу разбиваем на группы
						ORDER BY rating  -- Сортирует по рейтингу все записи
						ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING  -- Учитываем все строки
					   ) AS k
FROM  menu m
INNER JOIN pizzeria pz
ON (m.pizzeria_id = pz.id)
ORDER BY 1, 2;
