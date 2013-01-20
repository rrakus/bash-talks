#!/bin/bash
echo <(echo hi)
cat <(echo hi)

tar cf >(bzip2 -c > ./scripts.tar.bz2) *.sh
