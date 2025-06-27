cmake_minimum_required(VERSION 3.5) # Updated to avoid deprecation warnings

project(PDC_Ass_3 LANGUAGES C)

find_package(OpenCL REQUIRED)

# First executable: conv_opencl
add_executable(conv_opencl conv_opencl.c)
target_link_libraries(conv_opencl PRIVATE OpenCL::OpenCL m)
target_compile_definitions(conv_opencl PRIVATE CL_TARGET_OPENCL_VERSION=100)

# Second executable: conv_scaler
add_executable(conv_scaler conv_scaler.c)
target_link_libraries(conv_scaler PRIVATE m)

set_target_properties(conv_opencl conv_scaler PROPERTIES 
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)
