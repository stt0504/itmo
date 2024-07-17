#!/bin/bash

names=()
surnames=()
for ((i=1; i<=1000; i++))
do
    names+=("Name$i")
    surnames+=("Surname$i")
done

for ((i=1; i<=NUM_RECORDS_INSTRUCTOR; i++))
 do
    name=${names[$((RANDOM % ${#names[@]}))]}

    surname=${surnames[$((RANDOM % ${#surnames[@]}))]}

    cost_per_hour=$((RANDOM%100 + 50))

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Instructor (Name, Surname, Cost_for_hour_lesson) VALUES ('$name', '$surname', $cost_per_hour);"
done
