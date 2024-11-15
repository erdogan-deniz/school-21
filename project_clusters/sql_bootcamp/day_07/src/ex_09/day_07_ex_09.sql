SELECT
	person.address AS address,
	ROUND(ROUND(MAX(age), 2) - (ROUND(MIN(age), 2)/ROUND(MAX(age), 2)), 2)  AS formula,
	ROUND(AVG(person.age), 2) AS average,
	(MAX(person.age) - (MIN(person.age) / AVG(person.age)) > AVG(person.age)) AS comparison
FROM person
GROUP BY person.address
ORDER BY address;
