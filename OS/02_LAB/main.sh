#!/bin/bash

# Q1: Write a script that displays a main menu and performs tasks based on the input value.
# Valid input values = {1, 2, 3, exit}.
# Note: Using if-else is not allowed; You must use Switch.
# The different options 1,2,3 will display the output as follow:

check=1
while ((check!=0))
do

    echo "Enter the otion : "
    echo "1. Task 1"
    echo "2. Task 2"
    echo "3. Task 3"
    echo "0. Exit"
    read operator

    case $operator in
        '1') ./task1.sh;;
        '2') ./task2.sh;;
        '3') ./task3.sh;;
        '0') check=0;;
    esac
done