#!/bin/bash


# Q-3. Write a shell script to print if entered number is prime number
# or not. It should support the following requirements.
#  The script should accept the input from the command line.
#  If you don’t input any data, then display an error message to execute the
# script correctly.

if [ "$#" -eq 0 ]
then
  echo "No arguments supplied"
  exit 1
fi

factor=0

for ((i=1; i<=$1; i++))
do
    if [ $(($1 % $i)) -eq 0 ]
    then
        factor=$(($factor + 1))
    fi
done

if [ $factor -le 2 ]
then
    echo "Prime"
else
    echo "Not Prime"
fi
