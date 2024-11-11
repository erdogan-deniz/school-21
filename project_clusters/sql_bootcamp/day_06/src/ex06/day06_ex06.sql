-- A "CREATE SEQUENCE" is used to generate a sequence of elements.
-- A "CYCLE" argument defines behavior after reaching the "MAXVALUE".
CREATE SEQUENCE seq_person_discounts
    START WITH 1
    INCREMENT BY 1
    MINVALUE 1
    NO MAXVALUE
    NO CYCLE;

-- A "setval" is used to set a pointer on the value of the sequence.
SELECT setval(
        'seq_person_discounts', 
        COALESCE((SELECT MAX(person_discounts.id) FROM person_discounts), 0) + 1
    );

-- A "nextval" is used to get a next value after a pointer.
ALTER TABLE person_discounts
    ALTER COLUMN id SET DEFAULT nextval('seq_person_discounts');
