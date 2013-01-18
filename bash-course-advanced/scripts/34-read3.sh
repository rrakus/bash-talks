#!/bin/bash
while IFS=: read -r name surname age
do
  printf 'field1:<%q> field2:<%q> field3<%d>\n' "$name" "$surname" "$age"
done < 02-readdata
