#!/bin/bash
echo $BASHPID
echo $$
(
  echo $BASHPID
  echo $$
)
BASHPID=666
echo $BASHPID
