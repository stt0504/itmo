#!/bin/bash

for ((i=1; i<=$NUM_RECORDS_VISIT_NUMBER; i++))
do
    ticket_id=$((RANDOM % $NUM_RECORDS_TICKET + 1))

    attraction_id=$((RANDOM % $NUM_RECORDS_ATTRACTION + 1))

    number=$((RANDOM % 100))

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Visit_number (Ticket_ID, Attraction_ID, Number) VALUES ($ticket_id, $attraction_id, $number);"
done
