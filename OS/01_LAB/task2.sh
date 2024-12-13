#!/bin/bash

# Q2. Draw the Pattern as shown below using only while loop and if else
# statement. Take the number of lines as input.

if [ "$#" -eq 0 ]
then
  echo "No arguments supplied"
  exit 1
fi

i=1
while [ $1 -ge $i ]
do
    j=1
    while (($j<=$(($1 - $i))))
    do
        echo -n " "
        j=$(($j + 1))
    done
    echo -n "*" 
    k=1
    while ((k<$(($i))))
    do
        echo -n " "
        k=$(($k + 1))
    done
    l=2
    while ((l<$(($i))))
    do
        echo -n " "
        l=$(($l + 1))
    done
    if [ $i -ne 1 ]
    then
        echo -n "*"
    fi
    echo "" 
    i=$(($i + 1))
done

i=2
while ((i<=$1))
do
    j=2
    while (($j<=$(($i))))
    do
        echo -n " "
        j=$(($j + 1))
    done
    echo -n "*" 
    k=$i
    while ((k<$(($1))))
    do
        echo -n " "
        k=$(($k + 1))
    done
    l=$i
    while ((l<$(($1-1))))
    do
        echo -n " "
        l=$(($l + 1))
    done
    if [ $i -ne $1 ]
    then
        echo -n "*"
    fi
    echo "" 
    i=$(($i + 1))
done
