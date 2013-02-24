#!/bin/bash
trapfpe()
{
  printf 'Floating point exception catched\n'
}

trapterm()
{
  printf 'No no, try harder\n'
}

trap 'trapfpe' SIGFPE
trap 'trapterm' SIGTERM SIGINT
printf 'List of trapped signals:\n'
trap
printf 'Send SIGFPE or SIGTERM to process ID %d\n' "$$"
while :; do
  sleep 9999&
  printf 'Sleep process ID %d\n' "$!"
  wait
done
