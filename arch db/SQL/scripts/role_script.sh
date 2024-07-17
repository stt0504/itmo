#!/bin/bash

PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "CREATE ROLE reader LOGIN"
PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "GRANT SELECT ON ALL TABLES IN SCHEMA public TO reader;"

PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "CREATE ROLE writer LOGIN"
PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "GRANT SELECT, INSERT, UPDATE ON ALL TABLES IN SCHEMA public TO writer;"

PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "CREATE ROLE grouprole NOLOGIN"
PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "GRANT SELECT, INSERT, UPDATE, DELETE ON ALL TABLES IN SCHEMA public TO grouprole;"

PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "CREATE USER analytic"
PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "GRANT SELECT ON TABLE Visitor TO analytic;"

n=5
for ((i=1; i<=n; i++))
do
    username="user$i"
    PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "CREATE USER $username"
    PGPASSWORD="postgres" psql -U "postgres" -d "postgres" -c "GRANT grouprole TO $username;"
done
