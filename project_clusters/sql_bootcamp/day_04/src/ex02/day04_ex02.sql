CREATE VIEW
    v_generated_dates AS
SELECT
    generated_date :: date
FROM
    generate_series (
        '2022-01-01' :: date,
        '2022-01-31' :: date,
        '1 day' :: interval
    ) AS generated_date
ORDER BY
    1;
