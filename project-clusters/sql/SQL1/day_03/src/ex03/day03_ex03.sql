WITH woman_visits AS (
					  SELECT pizzeria.name AS pizzeria_name
					  FROM pizzeria
					  JOIN person_visits
					  ON (person_visits.pizzeria_id = pizzeria.id)
					  JOIN person
					  ON (person.id = person_visits.person_id)
					  WHERE person.gender = 'female'
					 ),
man_visits AS (
			   SELECT pizzeria.name AS pizzeria_name
			   FROM pizzeria
			   JOIN person_visits
			   ON (person_visits.pizzeria_id = pizzeria.id)
			   JOIN person
		   	   ON (person.id = person_visits.person_id)
			   WHERE person.gender = 'male'
			  )
			  
(
 (
  SELECT *
  FROM woman_visits
 )
 EXCEPT ALL
 ( 
  SELECT *
  FROM man_visits
 )
)
UNION ALL
(
 (
  SELECT *
  FROM man_visits
 )
 EXCEPT ALL
 ( 
  SELECT *
  FROM woman_visits
 )
) ORDER BY 1;
