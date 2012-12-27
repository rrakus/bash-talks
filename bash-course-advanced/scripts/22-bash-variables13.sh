#!/bin/bash
p() {
  printf 'SECONDS: %d\n' "$SECONDS"
}

p
sleep 2; p
sleep 2; p
SECONDS=666; p
sleep 2; p
sleep 2; p
unset SECONDS
SECONDS=666; p
sleep 2; p
