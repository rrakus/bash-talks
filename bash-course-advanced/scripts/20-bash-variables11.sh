#!/bin/bash
p() {
  printf 'PWD: %s\n' "$PWD"
}
p
pushd "$HOME"
  p
popd
cd /etc
p
cd -
p
