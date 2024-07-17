#!/bin/bash

date=$(date -d "2023-06-06" +"%Y-%m-%s")

for ((i=1; i<=$NUM_INSTRUCTOR_SCHEDULE_DAYS; i++))
do
    date=$(date -d "$date +1 days" +"%Y-%m-%d")
    for ((j=1; j<=$NUM_INSTRUCTOR_AT_DAY; j++))
    do
        instructor_id=$((RANDOM % NUM_RECORDS_INSTRUCTOR + 1))
        start_hour=$((RANDOM % 18))
        start_time=$(printf "%02d:00:00" $start_hour)

        end_hour=$((start_hour + 1 + RANDOM % (23 - start_hour - 1)))
        end_time=$(printf "%02d:00:00" $end_hour)

        PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Instructor_schedule (Instructor_ID, Day, Start_time, End_time) VALUES ($instructor_id, '$date', '$start_time', '$end_time');"
    done
done