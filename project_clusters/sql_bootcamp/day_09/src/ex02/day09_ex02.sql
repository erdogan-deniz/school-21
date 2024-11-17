CREATE FUNCTION fnc_trg_person_delete_audit()
RETURNS TRIGGER AS $$
    BEGIN
        INSERT INTO person_audit (
            row_id,
            name,
            age,
            gender,
            address
            )
        VALUES (
            OLD.id,
            OLD.name,
            OLD.age,
            OLD.gender,
            OLD.address
        );

        RETURN OLD;
    END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER trg_person_delete_audit 
AFTER DELETE ON person
FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;
