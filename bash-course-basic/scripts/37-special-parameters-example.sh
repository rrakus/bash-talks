#!/bin/bash
echo 'Difference between $* and $@'
for parameter in "$*"; do
  echo $parameter
  echo "$parameter"
  echo ---
done
echo 'end of $*'
for parameter in "$@"; do
  echo $parameter
  echo "$parameter"
  echo ---
done
echo 'end of $@'
