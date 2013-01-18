#!/bin/bash
while read -r name surname age
do
  printf 'Your name is %s %s and you are %d age old\n' "$name" "$surname" "$age"
done < 01-readdata
