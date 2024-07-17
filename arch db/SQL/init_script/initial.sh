#!/bin/bash

cd /migrations

if [ -z "$MIGRATION_VERSION" ]
then
  for sql_file in *.sql
   do
    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -f "$sql_file"
   done
else
  for sql_file in $(ls *.sql | sort -V)
   do
    migration_version=$(basename "$sql_file" .sql)

    if [[ $(printf "%s\n%s" "$migration_version" "$MIGRATION_VERSION" | sort -V | head -n1) == "$MIGRATION_VERSION" && $migration_version != $MIGRATION_VERSION ]]
     then
      break
    fi
    PGPASSWORD="$DB_PASSWORD" psql -U "$POSTGRES_USER" -d "$POSTGRES_DB" -f "$sql_file"
  done
fi

for sh_file in *.sh; do
    ./"$sh_file"
done




