SELECT *
FROM person_order
WHERE MOD(id, 2)=0
ORDER BY id DESC;