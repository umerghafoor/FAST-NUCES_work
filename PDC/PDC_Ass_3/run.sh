# rm -rf build
# rm -rf output
# cmake -S . -B ./build
# cmake --build ./build --config Release

# mkdir output
# mkdir output/scaler
# mkdir output/opencl
# mkdir output/scaler/dataset3
# mkdir output/opencl/dataset3

# # mkdir output/stargan-v2
# # mkdir output/stargan-v2/data
# # mkdir output/stargan-v2/data/afhq
# # mkdir output/stargan-v2/data/afhq/train
# # mkdir output/stargan-v2/data/afhq/train/cat/


# echo "Running CPU code"
# ./build/conv_scaler dataset3

# echo "Running OpenCL code"
# ./build/conv_opencl dataset3


# Compilation
gcc -o build/circle_openmp circle_openmp.c -fopenmp -lm -lSDL2
gcc -o build/circle_scaler circle_scaler.c -lm -lSDL2


echo "Compilation successful."
echo "Running the openmp program..."
./build/circle_openmp 1000 5440 4
echo "Running the scaler program..."
./build/circle_scaler 1000 5440

echo "Testing for different number of points..."
for i in 1000 # 2000 4000 8000 16000 32000 64000
do
    echo "Running the openmp program with $i points..."
    ./build/circle_openmp $i 5440 4
    ./build/circle_scaler $i 5440
done

echo "Testing for different resolutions..."
for i in 1000 # 2000 4000 8000 16000 32000 64000
do
    echo "Running the openmp program with $i points..."
    ./build/circle_openmp 1000 $i 4
    ./build/circle_scaler 1000 $i
done