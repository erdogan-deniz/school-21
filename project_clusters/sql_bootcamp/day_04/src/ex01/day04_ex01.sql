(
    SELECT
        name AS name
    FROM
        v_persons_female
)
UNION
(
    SELECT
        name
    FROM
        v_persons_male
)
ORDER by
    1;
