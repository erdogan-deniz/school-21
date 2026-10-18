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
WHERE last_point = 'a' AND LENGTH(tour) = 8
ORDER BY total_cost, tour