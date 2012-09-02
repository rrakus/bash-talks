#!/bin/bash
edir='/tmp/empty'
rm -rf "$edir"
mkdir "$edir"
shopt -s nullglob
for file in "$edir"/*
do
  echo "$file"
done
touch "$edir"/file{1..3}
for file in "$edir"/*
do
  echo "$file"
done
rm -rf "$edir"
mkdir "$edir"
shopt -u nullglob
for file in "$edir"/*
do
  echo "$file"
done
touch "$edir"/file{1..3}
for file in "$edir"/*
do
  echo "$file"
done
