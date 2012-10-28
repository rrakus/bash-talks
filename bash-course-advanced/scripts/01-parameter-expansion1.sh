#!/bin/bash
# variable a is set and have value
# varibale b is only set, without value
# variable c is unset
unset a b c
a="set and have value"
b=

echo ${a:-"word used"}
echo ${b:-"word used"}
echo ${c:-"word used"}
echo ${a-"word used"}
echo ${b-"word used"}
echo ${c-"word used"}

