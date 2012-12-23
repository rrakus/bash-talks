#!/bin/bash
echo 'START LINENO = '$LINENO

f1() {
echo 'f1 LINENO = '$LINENO
}

f2() {
echo 'f2 LINENO = '$LINENO
}
f1;f2
echo 'END LINENO = '$LINENO
