#!/bin/bash
echo "GLOBIGNORE = $GLOBIGNORE"
printf '<%s>\n' 0*
GLOBIGNORE=*2.sh:*4*.sh
echo "GLOBIGNORE = $GLOBIGNORE"
printf '<%s>\n' 0*
