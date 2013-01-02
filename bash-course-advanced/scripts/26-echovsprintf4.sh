#!/bin/bash
red='\e[0;31m'
green='\e[0;32m'
off='\e[0m'

printf 'RED: %b%s%b\n' "$red" "$1" "$off"
printf 'GREEN: %b%s%b\n' "$green" "$1" "$off"
printf '%s\n' ++++
printf 'RED no-off: %b%s\n' "$red" "$1"
printf 'GREEN no-off: %b%s\n' "$green" "$1"
printf '%s\n' ++++
