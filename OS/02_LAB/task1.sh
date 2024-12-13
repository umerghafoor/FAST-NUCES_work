#!/bin/bash

# 1. Input a filename from the user and display permissions of that particular file. Then invert
# the permissions e.g. If permissions were -r change them to not readable. Then again
# display the updated permissions of that file.
echo "File :"
read file

if [ -f $file ]
then
    if [ -r $file ]
    then
        echo "File is Readable"
        chmod -r $file
        echo "Permistion removed"
        ls -l $file | cut -d ' ' -f 1 
    else
        echo "File is not Readable"
        chmod +r $file
        echo "Permistion granted"
        ls -l $file | cut -d ' ' -f 1 
    fi
    
    if [ -w $file ]
    then
        echo "File is writeable"
        chmod -w $file
        echo "Permistion removed"
        ls -l $file | cut -d ' ' -f 1 
    else
        echo "File is not writeable"
        chmod +w $file
        echo "Permistion granted"
        ls -l $file | cut -d ' ' -f 1 
    fi
    
    if [ -x $file ]
    then
        echo "File is executable"
        chmod -x $file
        echo "Permistion removed"
        ls -l $file | cut -d ' ' -f 1 
    else
        echo "File is not executable"
        chmod +x $file
        echo "Permistion granted"
        ls -l $file | cut -d ' ' -f 1 
    fi
else
    echo "File not found"
fi
