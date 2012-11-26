#!/bin/bash
FUNCNEST=$1
printf 'FUNCNEST = %s\n' "$FUNCNEST"
f()
{
 ((i++))
 f
}
i=0
f
printf 'Nested %d times\n' "$i"
