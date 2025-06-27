#!/bin/bash

C_FILE="task1.c"
EXE_FILE="task1"
OUTPUT_FILE="benchmark_results.csv"

sizes=(8 64 256 512 1024 2048 4096 8192 16384)

echo "Matrix Size,Scalar 2D Time,Scalar 1D Time,SIMD Time" > $OUTPUT_FILE

for size in "${sizes[@]}"; do
    echo "Running task1 with N=$size..."

    # Modify the source file to update N
    sed -i "s/^#define N [0-9]\+/#define N $size/" "$C_FILE"

    # Compile the modified source file
    gcc -O3 -march=native -ffast-math -o $EXE_FILE $C_FILE -mavx

    # Run the compiled program and capture output
    result=$(./$EXE_FILE 2>&1)

    # Handle memory allocation errors
    if echo "$result" | grep -q "Error: Memory allocation failed"; then
        echo "$size,OUT_OF_MEMORY,OUT_OF_MEMORY,OUT_OF_MEMORY" >> $OUTPUT_FILE
        continue
    fi

    # Extract execution times
    scalar2D_time=$(echo "$result" | grep "Scalar 2D time" | awk '{print $NF}')
    scalar1D_time=$(echo "$result" | grep "Scalar 1D time" | awk '{print $NF}')
    simd_time=$(echo "$result" | grep "SIMD time" | awk '{print $NF}')

    # Check if the program crashed
    if [ -z "$scalar2D_time" ] || [ -z "$scalar1D_time" ] || [ -z "$simd_time" ]; then
        echo "$size,SEGFAULT,SEGFAULT,SEGFAULT" >> $OUTPUT_FILE
    else
        echo "$size,$scalar2D_time,$scalar1D_time,$simd_time" >> $OUTPUT_FILE
    fi
done

echo "Benchmark results saved to $OUTPUT_FILE"
