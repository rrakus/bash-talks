#!/bin/bash
foo=bar
baz="Will be splitted?"
for name in $foo $bar $baz; do echo $name; done
for name in "$foo $bar $baz"; do echo $name; done
for name in '$foo $bar $baz'; do echo $name; done
for name in "$foo" "$bar" "$baz"; do echo $name; done
for name in $foo "$bar $baz"; do echo "$name"; done
