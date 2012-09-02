#!/bin/bash
for file in *; do
  echo file: "$file"
done
rm *
for dir in */; do
  echo directory: "$dir"
done
for hidden in .*; do
  echo hidden: "$hidden"
done
for f in *dir*/*file.???; do echo $f done
