#!/bin/bash
var="123456789" # string with length 9
arr=(1st 2nd 3rd 4th 5th 6th 7th 8th 9th) # indexed array with 9 elements
printf '[%s]\n' "${var:1:3}"
printf '[%s]\n' "${var: -4:3}"
printf '[%s]\n' "${var:1:-3}"
echo
printf '[%s]\n' "${arr[@]:1:3}"
printf '[%s]\n' "${arr[@]: -4:3}"
echo
printf '[%s]\n' "${@:1:3}"
printf '[%s]\n' "${@: -4:3}"
