#!/bin/bash
p()
{
  printf '%s\n' "PIPESTATUS:"
  printf '%s\n' "$@"
  printf '%s\n' "++++"
}

p "${PIPESTATUS[@]}"
ls | sort | uniq | grep -q file | wc -l
p "${PIPESTATUS[@]}"
true | false | true | /not/a/command | true
p "${PIPESTATUS[@]}"
printf '%q\n' $(head -n66 /dev/urandom) | head -n1 | cat | sort | uniq | wc -l
p "${PIPESTATUS[@]}"
