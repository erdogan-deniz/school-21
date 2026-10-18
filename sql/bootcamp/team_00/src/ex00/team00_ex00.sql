CREATE TABLE tsp (
	point1 char NOT NULL,
	point2 char NOT NULL,
	cost int);
INSERT INTO tsp VALUES ('a', 'b', 10);
INSERT INTO tsp VALUES ('b', 'a', 10);
INSERT INTO tsp VALUES ('a', 'd', 20);
INSERT INTO tsp VALUES ('d', 'a', 20);
INSERT INTO tsp VALUES ('a', 'c', 15);
INSERT INTO tsp VALUES ('c', 'a', 15);
INSERT INTO tsp VALUES ('b', 'c', 35);
INSERT INTO tsp VALUES ('c', 'b', 35);
INSERT INTO tsp VALUES ('d', 'b', 25);
INSERT INTO tsp VALUES ('b', 'd', 25);
INSERT INTO tsp VALUES ('d', 'c', 30);
INSERT INTO tsp VALUES ('c', 'd', 30);

WITH RECURSIVE r AS (
SELECT 0 AS total_cost, '' AS tour, 'a'::char AS last_point
UNION ALL
SELECT r.total_cost+tsp.cost, 
	r.tour || ',' || tsp.point2, 
	tsp.point2 AS last_point 
FROM tsp
JOIN r ON
tsp.point1 = r.last_point AND r.tour NOT LIKE '%' || tsp.point2 || '%'
)
SELECT total_cost, '{a' || tour || '}' AS tour FROM r
WHERE last_point = 'a' 
	AND LENGTH(tour) = 8 
	AND total_cost = (SELECT MIN(total_cost) FROM r WHERE last_point = 'a' AND LENGTH(tour) = 8)
ORDER BY 1,2