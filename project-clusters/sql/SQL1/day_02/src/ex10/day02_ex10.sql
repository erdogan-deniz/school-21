SELECT
	  person.name AS person_name1,
	  person_name2 AS person_name2,
	  address AS common_address
FROM person
JOIN (
	  SELECT person.name AS person_name2,
			 person.address AS person_address,
			 person.id AS person_new_id
	  FROM person
	 ) AS tabl
ON (person.address = tabl.person_address)
WHERE
	 (address = person_address) AND
	 (id != person_new_id) AND
	 (id > person_new_id)
ORDER BY
	 	person_name1,
		person_name2;

