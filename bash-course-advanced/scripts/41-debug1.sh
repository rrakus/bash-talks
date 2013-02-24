#!/bin/bash
val=0
fce()
{
  local i
  for i in "${!BASH_SOURCE[@]}"; do
    printf '%s[%d]<-' "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  printf '\nval = %s\n' "$val"
} >&2
trap 'fce "$LINENO"' DEBUG

for i in a b c
do
  ((++val))
  echo "$i"
done
