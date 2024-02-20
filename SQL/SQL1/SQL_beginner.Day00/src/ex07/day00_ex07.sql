SELECT id, name,
	
	CASE
		WHEN (age>=10) AND (age<=20) THEN 'interval #1'
		WHEN (age>20) AND (age<24) THEN 'interval #2'
		ELSE 'interval #3'
	END interval_info

FROM person
ORDER BY interval_info;