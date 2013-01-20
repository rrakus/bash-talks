#!/bin/bash
# Process output from some program
re_patch='^%patch([[:digit:]]+)[[:space:]]+(.*)'
declare -a patches
while IFS= read -r line
do
#  echo $line
  if [[ $line =~ $re_patch ]]; then
    i="${BASH_REMATCH[1]}"
    opts="${BASH_REMATCH[2]}"
    patches["$((10#$i))"]="$opts"
  fi
done < <(grep -- '\%' ~/koji/bash/bash.spec)

for i in "${!patches[@]}"; do
  printf 'Patch number %d with options <%s>\n' "$i" "${patches[$i]}"
done
