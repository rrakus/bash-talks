#!/bin/bash
_echo()
{
  echo "$@"
}

_printf()
{
  printf '%s\n' "$@"
}
echo ECHO:
_echo "$@"
echo PRINTF:
_printf "$@"
