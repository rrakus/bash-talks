#!/bin/bash
read -p 'Name: ' name
read -p 'Surname: ' surname
read -p 'Age: ' age

printf 'Your name is %s %s and you are %d age old\n' "$name" "$surname" "$age"
