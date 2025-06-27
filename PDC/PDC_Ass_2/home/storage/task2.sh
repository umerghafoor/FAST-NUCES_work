#!/bin/bash


# Compile the code to be used by the main code
mpic++ msa_parallel.cpp -o msa_parallel -lfftw3
g++ -o msa_serial msa_serial.cpp -lfftw3

# Compile the main code
# This code will be used to run the parallel and serial code
# This code is used for measuring the time taken by the parallel and serial code
g++ -o msa_main msa_main.cpp -lfftw3

# Run the main code
./msa_main