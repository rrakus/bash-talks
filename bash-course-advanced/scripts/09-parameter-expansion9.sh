#!/bin/bash
var=foobarbazfoobarbaz
echo 'f:' "${var^f}"
echo 'b:' "${var^b}"
echo 'fb:' "${var^fb}"
echo '[fb]:' "${var^[fb]}"
echo 'fo:' "${var^fo}"
echo '*': "${var^*}"
echo 'f:' "${var^^f}"
echo 'b:' "${var^^b}"
echo 'fb:' "${var^^fb}"
echo '[fb]:' "${var^^[fb]}"
echo 'fo:' "${var^^fo}"
echo '*:' "${var^^*}"
