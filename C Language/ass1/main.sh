#!/bin/bash

# Function to run a task
run_task() {
    task_name=$1
    echo "Running $task_name..."
    if [ "$task_name" = "safedelete" ]; then
        read -p "Enter file path: " file_path
        ./$task_name.sh "$file_path"
    else
        ./$task_name.sh
    fi
}

# Main menu
while true; do
    echo "Choose a task to run:"
    echo "1. Task 1 processor details"
    echo "2. Task 2 test directory "
    echo "3. Task 3 safe delete"
    echo "4. Task 4 code editor"
    echo "0. Exit"
    
    read -p "Enter your choice: " choice
    
    case $choice in
        1)
            run_task "process"
            ;;
        2)
            run_task "task2"
            ;;
        3)
            run_task "safedelete"
            ;;
        4)
            run_task "task4"
            ;;
        0)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a number between 0 and 4."
            ;;
    esac
done
