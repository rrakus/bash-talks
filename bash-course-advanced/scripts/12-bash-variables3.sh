#!/bin/bash
f1() {
  for i in ${!FUNCNAME[@]}; do
    printf '%s at %s[%s]\n' "${FUNCNAME[$i]}" "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  echo '^^ f1 ^^'
  f2
}
f2() {
  for i in ${!FUNCNAME[@]}; do
    printf '%s at %s[%s]\n' "${FUNCNAME[$i]}" "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  echo '^^ f2 ^^'
}
f1 && echo ===
f2 && echo ===
