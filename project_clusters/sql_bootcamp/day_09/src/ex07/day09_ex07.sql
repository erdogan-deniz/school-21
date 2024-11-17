CREATE FUNCTION func_minimum(VARIADIC arr numeric[])
RETURNS numeric AS $$
DECLARE
    min_val numeric;
BEGIN
    min_val := arr[1];

    FOR i IN 2..array_length(arr, 1) LOOP
        IF arr[i] < min_val THEN
            min_val := arr[i];
        END IF;
    END LOOP;

    RETURN min_val;
END;
$$ LANGUAGE plpgsql;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
