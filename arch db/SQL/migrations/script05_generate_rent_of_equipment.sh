#!/bin/bash

for ((i=0; i<$NUM_RECORDS_RENT_OF_EQUIPMENT; i++))
do
    visitor_id=$((RANDOM % $NUM_RECORDS_VISITOR + 1))
    equipment_id=$((RANDOM % $NUM_RECORDS_EQUIPMENT + 1))

    year=$(shuf -i 2000-2023 -n 1)
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

    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Rent_of_equipment (Visitor_ID, Equipment_ID, Start_time, End_time) VALUES ($visitor_id, $equipment_id, '$start_time', '$end_time');"
done
