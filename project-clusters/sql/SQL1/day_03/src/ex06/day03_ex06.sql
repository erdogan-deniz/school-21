SELECT
	  menu.pizza_name AS pizza_name,
	  pizzeria.name AS pizzeria_name_1,
	  sec_pizzeria.name AS pizzeria_name_2,
	  menu.price AS price
FROM pizzeria
JOIN menu
ON (pizzeria.id = menu.pizzeria_id)
JOIN (
 	  SELECT
			pizzeria.id AS id,
			pizzeria.name AS name,
			menu.pizzeria_id AS pizzeria_id,
			menu.pizza_name AS pizza_name,
			menu.price AS price
 	  FROM pizzeria
 	  JOIN menu
 	  ON (pizzeria.id = menu.pizzeria_id)
	 ) AS sec_pizzeria
ON
  (menu.pizza_name = sec_pizzeria.pizza_name) AND
  (menu.price = sec_pizzeria.price) AND
  (pizzeria.name != sec_pizzeria.name)
WHERE (pizzeria.id > sec_pizzeria.id)
ORDER BY pizza_name;
