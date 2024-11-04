SELECT person.name AS name
FROM person
WHERE
	 (person.age > 25) AND
	 (person.gender = 'female')
ORDER BY name;
