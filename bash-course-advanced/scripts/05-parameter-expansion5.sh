#!/bin/bash
var="123456789" # string with length 9
arr=(1th 2th 3th 4th 5th 6th 7th 8th) # indexed array with 8 elements - how Red Hat number the floors
printf '[%s]\n' "${#var}"
printf '[%s]\n' "${#arr}" # length of the first element
printf '[%s]\n' "${#arr[@]}"
printf '[%s]\n' "${#@}"
