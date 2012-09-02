#!/bin/bash
./test.sh
foobarbaz="Set for this command only" ./test.sh
echo "$foobarbaz"
export foobarbaz="exported variable"
./test.sh
echo "$foobarbaz"
