#!/bin/bash
p() {
  printf 'RANDOM: %d\n' "$RANDOM"
}

(($1)) && RANDOM="$1"
p && p
