SELECT 
    person.name AS name,
    COUNT(*) AS count_of_visits
FROM 
    person_visits
INNER JOIN 
    person ON person_visits.person_id = person.id
GROUP BY 
    person.name
ORDER BY 
    count_of_visits DESC,
    person.name ASC
-- A "LIMIT" clause allows us to take only a defined count of entities.
LIMIT 4;
