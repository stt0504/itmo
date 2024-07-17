#!/bin/bash

for ((i=1; i<=$NUM_RECORDS_ATTRACTION; i++))
do
    name="Attraction$i"

    required_age=$((RANDOM % 18 + 1))

    description=$(head /dev/urandom | tr -dc 'a-zA-Z0-9 ' | fold -w 255 | head -n 1)

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Attraction (Name, Required_age, Description) VALUES ('$name', $required_age, '$description');"
done