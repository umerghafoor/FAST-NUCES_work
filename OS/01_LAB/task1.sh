#!/bin/bash

# Q-1. Program should take takes two numbers as command line
# arguments and an operator from the user and be able to perform the
# calculations. (USE switch-case).

if [ "$#" -eq 0 ]
then
  echo "No arguments supplied"
  exit 1
fi

echo $1 $2

echo "Enter the operator : "
read operator

case $operator in 
    +) echo $(($1 + $2));;
    -) echo $(($1 - $2));;
    x) echo $(($1 * $2));;
    /) echo $(($1 / $2));;
esac