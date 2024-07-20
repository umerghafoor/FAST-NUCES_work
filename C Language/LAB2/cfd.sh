#!/bin/bash

if [ "$1" = "-d" ]; then
    mkdir "$2"
    echo "Directory with name '$2' created successfully."

elif [ "$1" = "-f" ]; then
    if [ -z "$2" ]; then
        echo "filename is missing."
        exit 1
    fi
    
    touch "$2.txt"
    filename="$2.txt"
    
    if [ "$3" = "-t" ]; then
        if [ -z "$4" ]; then
            echo "Text is missing."
            exit 1
        fi
        
        echo "$4" > "$filename"
        echo "Successfull wrote the text."
    else
        
        exit 1
    fi

else
   
    exit 1
fi

