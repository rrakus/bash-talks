#!/bin/bash

p()
{
  printf 'IFS=%q\n' "$IFS"
  printf '<%s>' "$@"
  echo
}

v="a  b- c.* ..d"
p $(date)
p $v
p $((2**10 + 21))

IFS='.0:'
p $(date)
p $v
p $((2**10 + 21))

p "$(date)"
p "$v"
p "$((2**10 + 21))"
