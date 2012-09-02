#!/bin/bash
var=dog
case $var in
  dog|horse|cat) echo "It has 4 legs";;
  man|kangaroo) echo "It has 2 legs";;
  *) echo "I don't know what is $var";;
esac
