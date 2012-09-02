#!/bin/bash
case $1 in
  "") echo "argument 1 not set or empty";;
  a*) echo "It beggins with a";;
  ???) echo "It has 3 characters";;
  *b*) echo "It has b character";;
  *) echo "It's everything else";;
esac
