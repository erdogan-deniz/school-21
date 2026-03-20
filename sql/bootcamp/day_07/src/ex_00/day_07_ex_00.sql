SELECT 
    person_visits.person_id AS person_id,
    COUNT(*) AS count_of_visits
FROM 
    person_visits
-- A "GROUP BY" clause splits the data by the field.
GROUP BY 
    person_visits.person_id
ORDER BY 
    count_of_visits DESC,
    person_visits.person_id ASC;
