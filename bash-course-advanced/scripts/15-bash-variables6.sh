#!/bin/bash
var="Hello my _fuc*ing_ World"
myprint()
{
  printf 'IFS: %q\n' "$IFS"
  printf '<%s>\n' $var
}

myprint
IFS= myprint
IFS='_' myprint
IFS='*yd:' myprint
