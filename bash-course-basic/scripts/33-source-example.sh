#!/bin/bash
echo "$lib_version"
. test_source.sh
echo "$lib_version"
is_running "bash" && echo "bash is running"
is_running "firefox" && echo "firefox is running"
