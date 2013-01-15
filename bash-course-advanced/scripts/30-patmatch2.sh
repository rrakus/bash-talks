#!/bin/bash
re_alnum='^[[:blank:]]*([[:alnum:]]+)[[:blank:]]*'
if [[ $1 =~ $re_alnum ]]; then
  printf 'MATCH: %s\n' "${BASH_REMATCH[1]}"
else
  echo NOT MATCH
fi
