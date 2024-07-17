#!/bin/bash

for ((i=1; i<=NUM_RECORDS_COMMENT; i++))
do
    visitor_id=$((RANDOM % $NUM_RECORDS_VISITOR + 1))

    year=$(shuf -i 2000-2023 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    hour=$(shuf -i 0-23 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)
    visit_date="$year-$month-$day $hour:$minute:$second"

    year=$(shuf -i $((year+1))-2024 -n 1)
    month=$(shuf -i 1-12 -n 1)
    day=$(shuf -i 1-28 -n 1)
    hour=$(shuf -i 0-23 -n 1)
    minute=$(shuf -i 0-59 -n 1)
    second=$(shuf -i 0-59 -n 1)

    comment_date="$year-$month-$day $hour:$minute:$second"

    rating=$((RANDOM % 5 + 1 ))
    description=$(head -c 1000 /dev/urandom | LC_CTYPE=C tr -dc 'a-zA-Z0-9 ')
    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Comment (Visitor_ID, Visit_date, Comment_date, Rating, Description) VALUES ($visitor_id, '$visit_date', '$comment_date', $rating, '$description');"
done