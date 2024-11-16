-- Session № 1:
-- SELECT pg_backend_pid();
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
COMMIT;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session № 2:
-- SELECT pg_backend_pid();
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
COMMIT;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
