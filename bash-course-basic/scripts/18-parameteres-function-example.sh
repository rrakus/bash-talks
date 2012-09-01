#!/bin/bash
fce()
{
  if [[ $# -lt 2 ]]; then
    return 1
  fi
  echo $2
  echo $1
}

fce 1 2
fce 2 1
fce "1 2"
fce 1
