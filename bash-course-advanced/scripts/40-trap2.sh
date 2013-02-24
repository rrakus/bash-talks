#!/bin/bash
tempfile=$(mktemp)
clean(){
  printf 'Cleaning\n'
  rm -rf "$tempfile"
}
trap clean EXIT
file "$tempfile"
printf "I'm doing anything\n"
sleep 5
printf "I'm done\n"
