#!/bin/bash
dir=/tmp/pathtest
rm -rf "$dir"; mkdir -p "$dir"; touch "$dir"/a
opath=$PATH
ppath()
{
  printf 'PATH:\n'
  printf '%s\n' "$PATH"
}

ppath; ls "$dir"
hash; type ls
PATH='/:~/bin'
hash; type ls
ppath; ls "$dir"
hash; type ls
PATH=$opath
hash; type ls
ppath; ls "$dir"
hash; type ls
