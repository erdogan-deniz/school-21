SELECT
	  name,
	  max AS rating
FROM (
	  SELECT
			name,
			MAX(rating),
			SUM(person_id)
	  FROM pizzeria 
	  LEFT JOIN person_visits
	  ON (pizzeria.id = person_visits.pizzeria_id)
	  GROUP BY pizzeria.name
	 ) AS temporary
WHERE sum IS NULL;
