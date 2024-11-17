CREATE TABLE person_audit
(
    created TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP NOT NULL,
    type_event CHAR(1) DEFAULT 'I' NOT NULL,
    row_id BIGINT,
    name VARCHAR NOT NULL,
    age INTEGER NOT NULL DEFAULT 10,
    gender VARCHAR DEFAULT 'female' NOT NULL,
    address VARCHAR,

    CONSTRAINT ch_type_event CHECK(type_event in ('I', 'U', 'D'))
);

CREATE FUNCTION fnc_trg_person_insert_audit()
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
            NEW.id,
            NEW.name,
            NEW.age,
            NEW.gender,
            NEW.address
        );

        RETURN NEW;
    END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER trg_person_insert_audit
AFTER INSERT ON person
FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk')
