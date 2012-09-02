#!/bin/bash
arr=(jedna dve tri)
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}
for i in "${arr[@]}"; do
  echo "$i"
done
