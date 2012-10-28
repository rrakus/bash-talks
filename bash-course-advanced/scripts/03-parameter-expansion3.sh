#!/bin/bash
echo "The 1st parameter is: ${1:?Parameter 1 is not set}"
echo "The 2nd parameter is: ${2:?}"
