#!/bin/bash
re_bash_line_comment='^[[:blank:]]*#(.*)$'
while IFS= read -r line
do
  if [[ $line =~ $re_bash_line_comment ]]; then
    continue
  else
    printf '%s\n' "$line"
  fi
done
