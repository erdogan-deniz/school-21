SELECT
    visit_date AS action_date,
    (
        SELECT
            name AS person_name
        FROM
            person
        WHERE
            (person.id = person_visits.person_id)
    )
FROM
    person_visits
INTERSECT
SELECT
    order_date AS action_date,
    (
        SELECT
            name AS person_name
        FROM
            person
        WHERE
            (person.id = person_order.person_id)
    )
FROM
    person_order
ORDER BY
    action_date,
    person_name DESC;
