#!/bin/bash
a=10
b=1
op1="+"
op2="-"
((c=a $op1 b $op2 a $op1 b))
echo $a $b $c
