#!/bin/bash

for ((i=1; i<=$NUM_RECORDS_APPOINTMENT; i++))
do
    ticket_id=$((RANDOM % $NUM_RECORDS_TICKET + 1))

    attraction_id=$((RANDOM % $NUM_RECORDS_ATTRACTION + 1))

    year=$(shuf -i 2000-2022 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    hour=$(shuf -i 0-22 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)
    start_time="$year-$month-$day $hour:$minute:$second"

    hour=$(shuf -i $((hour+1))-23 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)
    end_time="$year-$month-$day $hour:$minute:$second"


    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Appointment (Ticket_ID, Attraction_ID, Start_time, End_time) VALUES ($ticket_id, $attraction_id, '$start_time', '$end_time');"
done