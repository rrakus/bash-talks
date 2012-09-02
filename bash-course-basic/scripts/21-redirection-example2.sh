#!/bin/bash
echo Hello World > output.txt
cat output.txt
echo Hello World 2> output.txt
cat output.txt
echo Hello World >> output.txt
cat output.txt
this_command_doesn_exist &>> output.txt
cat output.txt
