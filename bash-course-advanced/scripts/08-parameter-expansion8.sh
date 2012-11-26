#!/bin/bash
var=foobarbazfoobarbaz
echo "${var/a/e}"
echo "${var/ar/eq}"
echo "${var/[obr]?[af]/X}"
echo "${var//a/e}"
echo "${var//ar/eq}"
echo "${var//o/e}"
echo "${var//[obr]?[af]/X}"
echo "${var/#foo/XXX}"
echo "${var/%foo/XXX}"
echo "${var/#baz/XXX}"
echo "${var/%baz/XXX}"
echo "${var/*o/X}"
