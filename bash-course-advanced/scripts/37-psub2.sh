#!/bin/bash
# Show differences between output of 2 programs
pn=bash-4.2-coverity.patch
f1=~/koji/bash/bash.spec
f2=~/brew/bash/bash.spec
diff -up <(grep -n "$pn" "$f1") <(grep -n "$pn" "$f2")
