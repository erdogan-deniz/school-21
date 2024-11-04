SELECT pizzeria.name AS pizzeria_name
FROM pizzeria
WHERE pizzeria.id IN (
					  (
					   (
						SELECT pizzeria.id
					    FROM pizzeria
						JOIN menu
						ON (pizzeria.id = menu.pizzeria_id)
						JOIN person_order
						ON (person_order.menu_id = menu.id)
						JOIN person
						ON (person.id = person_order.person_id)
						WHERE (person.gender = 'male')
					   )
					  EXCEPT
					   (
						SELECT pizzeria.id
						FROM pizzeria
						JOIN menu
						ON (pizzeria.id = menu.pizzeria_id)
						JOIN person_order
						ON (person_order.menu_id = menu.id)
						JOIN person
						ON (person.id = person_order.person_id)
						WHERE (person.gender = 'female')
					   )
					  )
					  UNION
					  (
					   (
						SELECT pizzeria.id
						FROM pizzeria
						JOIN menu
						ON (pizzeria.id = menu.pizzeria_id)
						JOIN person_order
						ON (person_order.menu_id = menu.id)
						JOIN person
						ON (person.id = person_order.person_id)
						WHERE (person.gender = 'female')
					   )
					   EXCEPT
					   (
						SELECT pizzeria.id
						FROM pizzeria
						JOIN menu
						ON (pizzeria.id = menu.pizzeria_id)
						JOIN person_order
						ON (person_order.menu_id = menu.id)
						JOIN person
						ON (person.id = person_order.person_id)
						WHERE (person.gender = 'male')
					   )
  					  )
					 )
ORDER BY pizzeria_name;
