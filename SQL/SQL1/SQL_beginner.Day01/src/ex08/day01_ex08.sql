SELECT	order_date,	CONCAT(name,	' (age:',	age,	')')	AS	person_information
FROM	person_order
NATURAL	JOIN	person
ORDER	BY	name,	age;