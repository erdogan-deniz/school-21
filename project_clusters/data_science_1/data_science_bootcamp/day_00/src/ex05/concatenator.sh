#!/bin/sh

HEADER="id,created_at,name,has_test,alternate_url"

RES_FILE="hh_positions.csv"

TAIL_FLAG="-n"
TAIL_FLAG_VAL="+2"

echo "$HEADER" > "$RES_FILE"

for file in *.csv; do
    if [ "$file" != "$RES_FILE" ]; then
        tail $TAIL_FLAG $TAIL_FLAG_VAL "$file" >> "$RES_FILE"
    fi
done

rm \"*.csv && clear
