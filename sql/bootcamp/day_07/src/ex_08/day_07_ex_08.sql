SELECT person.address AS address, pizzeria.name AS name, COUNT(person_order.id) AS count_of_orders
FROM person
INNER JOIN person_order
ON person.id = person_order.person_id
INNER JOIN menu
ON person_order.menu_id = menu.id
INNER JOIN pizzeria
ON menu.pizzeria_id = pizzeria.id
GROUP BY person.address, pizzeria.name
ORDER BY address, name;
