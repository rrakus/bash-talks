#!/bin/bash
for i in r{u,oma,u}n; do
  echo $i
done
mkdir dir{1..5}
touch dir{1..5}/file{001..125..33}
for i in {10..0}; do
  echo $i
done
echo BOOM
