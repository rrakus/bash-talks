#!/bin/bash
declare -A arr=( [vyska]=175 [vaha]=75 [vek]=28 )
echo "Vyska: ${arr[vyska]}"
echo "Vaha: ${arr[vaha]}"
echo "Vek: ${arr[vek]}"
for i in "${arr[@]}"; do
  echo "$i"
done
