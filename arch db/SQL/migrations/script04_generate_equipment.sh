#!/bin/bash

visitor_id=($(PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -t -c "SELECT Visitor_ID FROM Visitor;"))
shuf -e "${visitor_id[@]}" > shuffled_visitor_ids.txt

if [ "$NUM_RECORDS_VISITOR" -lt "$NUM_RECORDS_EQUIPMENT" ]
then
  min_records="$NUM_RECORDS_VISITOR"
else
  min_records="$NUM_RECORDS_EQUIPMENT"
fi

types=()
for ((i=1; i<=10; i++))
do
    types+=("Type$i")
done

for ((i=0; i<min_records; i++))
do
      equipment_type=${types[$((RANDOM % ${#types[@]}))]}
      visitor_id_value=$(head -n $((i+1)) shuffled_visitor_ids.txt | tail -n 1)
      PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Equipment (Type, Visitor_ID) VALUES ('$equipment_type', $visitor_id_value);"
done

for ((i=$NUM_RECORDS_VISITOR; i<$NUM_RECORDS_EQUIPMENT; i++))
do
      equipment_type=$(( RANDOM % 10 + 1 ))
      PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -c "INSERT INTO Equipment (Type) VALUES ('$equipment_type');"
done
