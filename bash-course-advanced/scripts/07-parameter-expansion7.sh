#!/bin/bash
var="foofoobarbazbaz"
printf '%s\n' "${var%baz}"
printf '%s\n' "${var%%baz}"
printf '%s\n' "${var%o*}"
printf '%s\n' "${var%%o*}"
printf '%s\n' "${@%?*[a-c]*?}"
