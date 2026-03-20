CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10)
RETURNS TABLE (fibonacci_num bigint) AS $$
DECLARE
    a bigint := 0;
    b bigint := 1;
BEGIN
    WHILE a < pstop LOOP
        RETURN QUERY SELECT a;

        b := a + b;
        a := b - a;
    END LOOP;

    RETURN;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fnc_fibonacci(100);
SELECT * FROM fnc_fibonacci();
