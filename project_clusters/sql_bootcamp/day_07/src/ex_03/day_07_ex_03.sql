-- A "WITH" is used to save the "SELECT" result to a temporary variable.
WITH visits AS (
    SELECT 
        person.name as name,
        COUNT(*) AS count_of_visits
    FROM 
        person_visits
    INNER JOIN 
        person ON person_visits.person_id = person.id
)

SELECT *
FROM 
    visits