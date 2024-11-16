-- Session № 1:
-- SELECT pg_backend_pid();
BEGIN;
UPDATE pizzeria SET rating = 1 WHERE id = 1;
UPDATE pizzeria SET rating = 1 WHERE id = 2;
COMMIT;

-- Session № 2:
-- SELECT pg_backend_pid();
BEGIN;
UPDATE pizzeria SET rating = 1 WHERE id = 2;
UPDATE pizzeria SET rating = 1 WHERE id = 1;
COMMIT;
