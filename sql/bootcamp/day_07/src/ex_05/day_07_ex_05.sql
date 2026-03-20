SELECT DISTINCT person.name AS name
FROM person
INNER JOIN person_visits
ON person.id = person_visits.person_id
ORDER BY name;

