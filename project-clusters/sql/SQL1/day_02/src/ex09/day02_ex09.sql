SELECT person.name AS name
FROM person
WHERE person.id IN (
					SELECT person_order.person_id
					FROM person_order
					JOIN menu
					ON (person_order.menu_id = menu.id)
					WHERE (pizza_name = 'cheese pizza')
					INTERSECT
					SELECT person_order.person_id
					FROM person_order
					JOIN menu
					ON (person_order.menu_id = menu.id)
					WHERE (pizza_name = 'pepperoni pizza')	
				   )
ORDER BY name;
