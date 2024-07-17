#!/bin/bash

date=$(date -d "2023-03-09" +"%Y-%m-%s")

for ((i=1; i<=$NUM_ATTRACTION_SCHEDULE_DAYS; i++))
do
    date=$(date -d "$date +1 days" +"%Y-%m-%d")
    for ((j=1; j<=$NUM_ATTRACTION_AT_DAY; j++))
    do
        attraction_id=$((RANDOM % NUM_RECORDS_ATTRACTION + 1))
        start_hour=$((RANDOM % 18))
        start_time=$(printf "%02d:00:00" $start_hour)

        end_hour=$((start_hour + 1 + RANDOM % (23 - start_hour - 1)))
        end_time=$(printf "%02d:00:00" $end_hour)

        PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Attraction_schedule (Attraction_ID, Day, Start_time, End_time) VALUES ($attraction_id, '$date', '$start_time', '$end_time');"
    done
done
