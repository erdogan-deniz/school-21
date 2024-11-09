SELECT
    COALESCE(person.name, '-') AS person_name,
    req_person_visits.visit_date AS visit_date,
    COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM
    (
        SELECT
            *
        FROM
            person_visits
        WHERE
            person_visits.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
    ) AS req_person_visits
    FULL OUTER JOIN person ON (person.id = req_person_visits.person_id)
    FULL OUTER JOIN pizzeria ON (req_person_visits.pizzeria_id = pizzeria.id)
ORDER BY
    person_name,
    pizzeria_name,
    visit_date;
