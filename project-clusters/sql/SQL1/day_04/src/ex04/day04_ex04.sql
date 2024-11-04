CREATE VIEW v_symmetric_union AS
WITH
  	R AS (
      	  SELECT person_visits.person_id AS person_id
      	  FROM person_visits
      	  WHERE (person_visits.visit_date = '2022-01-02')
     	 ),
  	S AS (
      	  SELECT person_visits.person_id AS person_id
      	  FROM person_visits
      	  WHERE (person_visits.visit_date = '2022-01-06')
     	 ),
  	L_bracket AS (
	  			  (
	  			   SELECT *
				   FROM R
  				  )
                  EXCEPT
          		  (
	  			   SELECT *
				   FROM S
  				  )
         		 ),
  	R_bracket AS (
          		  (
	  			   SELECT *
				   FROM S
  				  )
          		  EXCEPT
          		  (
	  			   SELECT *
				   FROM R
  				  )
         		 ),
  	res AS (
			(
	  		 SELECT *
			 FROM L_bracket
  			)
      		UNION
      		(
	  		 SELECT *
			 FROM R_bracket
  			)
           )

SELECT *
FROM res
ORDER BY 1;
