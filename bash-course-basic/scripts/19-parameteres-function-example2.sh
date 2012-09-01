#!/bin/bash
fce()
{
  while [[ $# -gt 0 ]]; do
    echo $1
    shift
  done
}
fce 1 2 3 4 5 6 7 8 9
fce "1 2 3 4 5 6 7 8 9"
fce "bread and butter" "fish and chips" "beers and girls"
fce ""
