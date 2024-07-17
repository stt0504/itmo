#!/bin/bash

visitor_id=($(PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -t -c "SELECT Visitor_ID FROM Visitor;"))
shuf -e "${visitor_id[@]}" > shuffled_visitor_ids.txt

for ((i=0; i<$NUM_RECORDS_VISITOR; i++))
do
    section_number=$(( RANDOM % 10 + 1 ))
    visitor_id_value=$(head -n $((i+1)) shuffled_visitor_ids.txt | tail -n 1)

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Locker (Visitor_ID, Section_number) VALUES ($visitor_id_value, $section_number);"
done

for ((i=$NUM_RECORDS_VISITOR; i<$NUM_RECORDS_LOCKER; i++))
do
    section_number=$(( RANDOM % 10 + 1 ))

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Locker (Section_number) VALUES ($section_number);"
done