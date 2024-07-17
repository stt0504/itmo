#!/bin/bash

names=()
surnames=()
for ((i=1; i<=1000; i++))
do
    names+=("Name$i")
    surnames+=("Surname$i")
done

for ((i=1; i<=NUM_RECORDS_VISITOR; i++))
 do
    name=${names[$((RANDOM % ${#names[@]}))]}

    surname=${surnames[$((RANDOM % ${#surnames[@]}))]}

    year=$(shuf -i 1950-2020 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    date="$year-$month-$day"

    digits=$(shuf -i 0-9 -n 10 | tr -d '\n')

    phone="+7$digits"

    email="email$i@example.com"

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Visitor (Name, Surname, Date_of_birth, Phone_number, Email) VALUES ('$name', '$surname', DATE '$date', '$phone', '$email');"
done
