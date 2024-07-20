#compile and run the minedit.c
gcc MinEdit.c -o MinEdit

if [ $? -eq 0 ]; then
    echo "Compilation successful."

    
    ./MinEdit
else
    echo "Compilation failed."
fi
