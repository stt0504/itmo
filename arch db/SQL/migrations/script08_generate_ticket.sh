#!/bin/bash

for ((i=1; i<=$NUM_RECORDS_TICKET; i++))
do
    year=$(shuf -i 2000-2022 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    hour=$(shuf -i 0-22 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)
    start_date="$year-$month-$day $hour:$minute:$second"

    year=$(shuf -i $((year+1))-2025 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    hour=$(shuf -i 0-22 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)
    finish_date="$year-$month-$day $hour:$minute:$second"

    visitor_id=$((RANDOM % $NUM_RECORDS_VISITOR + 1))

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Ticket (Start_date, Finish_date, Visitor_ID) VALUES (TIMESTAMP '$start_date', TIMESTAMP '$finish_date', $visitor_id);"
done
