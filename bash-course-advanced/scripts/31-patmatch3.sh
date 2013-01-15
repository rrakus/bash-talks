#!/bin/bash
re_alnum='([[:alpha:]]+):[[:blank:]]*([[:digit:]]+)'
if [[ $1 =~ $re_alnum ]]; then
  printf 'MATCH\n'
  printf 'String portion: <%s>\n' "${BASH_REMATCH[1]}"
  printf 'Number portion: <%d>\n' "${BASH_REMATCH[2]}"
  printf 'This matched entire regexp: <%s>\n' "${BASH_REMATCH[0]}"
else
  printf '<%s> does not match <%s>\n' "$1" "$re_alnum"
fi
