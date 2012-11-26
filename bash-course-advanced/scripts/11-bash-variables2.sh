#!/bin/bash
printf '<%s>\n' "${DIRSTACK[@]}" "---"
pushd /tmp >/dev/null
pushd / > /dev/null
pushd /home > /dev/null
printf '<%s>\n' "${DIRSTACK[@]}" "---"
DIRSTACK[3]="/just/modified"
printf '<%s>\n' "${DIRSTACK[@]}" "---"
popd > /dev/null
popd > /dev/null
popd > /dev/null
printf '<%s>\n' "${DIRSTACK[@]}" "---"
