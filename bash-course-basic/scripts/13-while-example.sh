#!/bin/bash
a="c"
b="cccc"
while [[ $a != $b ]];do echo "$a $b"; a="$a"c;done
while ./test_script.sh; do echo "test script returns 0"; done
a=2;b=10;while (( a < b )); do echo "$a < $b"; (( a+= 2 )); done

