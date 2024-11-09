(
    SElECT
        gen_ser :: date AS missing_date
    FROM
        generate_series('2022-01-01' :: date, '2022-01-31' :: date, '1 day') AS gen_ser
)
EXCEPT
(
    SELECT
        person_visits.visit_date AS visit_date
    FROM
        person_visits
)
ORDER BY
    1;
