#!/bin/bash
var="foofoobarbaz"
printf '%s\n' "${var#foo}"
printf '%s\n' "${var##foo}"
printf '%s\n' "${var#*a}"
printf '%s\n' "${var##*a}"
printf '%s\n' "${@#?[a-c]*?}"
