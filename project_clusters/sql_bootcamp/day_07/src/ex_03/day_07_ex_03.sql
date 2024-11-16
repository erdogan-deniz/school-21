WITH v AS
(SELECT pizzeria.name, COUNT (visit_date) AS count, 'visit' AS action_type
FROM person_visits INNER JOIN pizzeria ON pizzeria_id = pizzeria.id
GROUP BY pizzeria.name),
    o AS
(SELECT pizzeria.name, COUNT (order_date) AS count, 'order' AS action_type
FROM person_order INNER JOIN menu ON menu.id = menu_id
INNER JOIN pizzeria ON pizzeria_id = pizzeria.id
GROUP BY pizzeria.name)
SELECT v.name, v.count + o.count AS total_count
FROM v INNER JOIN o ON v.name = o.name
ORDER BY total_count DESC, name ASC;