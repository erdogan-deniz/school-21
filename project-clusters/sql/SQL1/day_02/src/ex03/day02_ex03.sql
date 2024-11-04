WITH req_visit_date AS (
						SELECT visit_date
						FROM person_visits
						WHERE
							 (person_id = 1) OR
							 (person_id = 2)
					   )

SELECT missing_date :: date
FROM generate_series (
					  '2022-01-01' :: date,
					  '2022-01-10' :: date,
					  '1 day' :: interval
					 ) AS missing_date
LEFT JOIN req_visit_date
ON (missing_date = visit_date)
WHERE (visit_date IS NULL)
ORDER BY missing_date;
