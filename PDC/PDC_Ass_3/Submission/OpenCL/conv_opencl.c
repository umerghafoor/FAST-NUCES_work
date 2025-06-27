#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CL/cl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "conv_util.h"

typedef struct {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
} OpenCLObjects;

const char* kernelSource = 
"__kernel void convolution(__global float* input, __global float* output, int width, int height) {  \n"
"    int x = get_global_id(0);                                                                \n"
"    int y = get_global_id(1);                                                                \n"
"    int offset = 1; // For a 3x3 kernel                                                      \n"
"    if (x >= offset && x < (width - offset) && y >= offset && y < (height - offset)) {         \n"
"        float sum = 0.0f;                                                                    \n"
"        for (int ky = 0; ky < 3; ky++) {                                                     \n"
"            for (int kx = 0; kx < 3; kx++) {                                                 \n"
"                int pixel_x = x + kx - offset;                                               \n"
"                int pixel_y = y + ky - offset;                                               \n"
"                float pixel = input[pixel_y * width + pixel_x];                              \n"
"                float kvalue = (kx == 0) ? 1.0f : ((kx == 1) ? 0.0f : -1.0f);                   \n"
"                sum += pixel * kvalue;                                                       \n"
"            }                                                                                \n"
"        }                                                                                    \n"
"        output[y * width + x] = sum;                                                         \n"
"    }                                                                                        \n"
"}                                                                                            \n";


///////////////////////////////////////////////////////////////////////////////
///                   Utity Functions                                     /////
/// Functions:                                                            /////
/// 1. loadImage                                                          /////
/// 2. convertImageToFloat                                                /////
/// 3. saveOutputImage                                                    /////
///////////////////////////////////////////////////////////////////////////////

unsigned char* loadImage(const char *filename, int *width, int *height, int *channels) {
    unsigned char *img = stbi_load(filename, width, height, channels, 1);
    if (!img) {
        printf("Failed to load image: %s\n", filename);
    }
    return img;
}

void convertImageToFloat(unsigned char *image, float *floatImage, int size) {
    for (int i = 0; i < size; i++) {
        floatImage[i] = (float)image[i] / 255.0f;
    }
}

void saveOutputImage(const char *filename, float *outputImage, int width, int height) {
    size_t img_size = width * height;
    unsigned char *outputImageUchar = (unsigned char *)malloc(img_size);
    for (size_t i = 0; i < img_size; i++) {
        outputImageUchar[i] = (unsigned char)(outputImage[i] * 255.0f);
    }
    stbi_write_png(filename, width, height, 1, outputImageUchar, width);
    free(outputImageUchar);
}

///////////////////////////////////////////////////////////////////////////////
///                   OpenCL Initialization                               /////
/// Steps:                                                                /////
/// 1. Get platform and device                                            /////
/// 2. Create context and command queue                                   /////
/// 3. Create program and build it                                        /////
/// 4. Create kernel                                                      /////
/// 5. Set kernel arguments                                               /////
///////////////////////////////////////////////////////////////////////////////

OpenCLObjects initOpenCL(const char *kernelSource, int width, int height) {
    OpenCLObjects ocl;
    cl_int err;
    
    // Get platform and device
    err = clGetPlatformIDs(1, &ocl.platform, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to find an OpenCL platform!\n");
        exit(EXIT_FAILURE);
    }
    
    // Try to get a GPU device first.
    err = clGetDeviceIDs(ocl.platform, CL_DEVICE_TYPE_GPU, 1, &ocl.device, NULL);
    if (err != CL_SUCCESS) {
        // Fall back to CPU if no GPU is available.
        printf("Warning: No GPU device found, falling back to CPU...\n");
        err = clGetDeviceIDs(ocl.platform, CL_DEVICE_TYPE_CPU, 1, &ocl.device, NULL);
        if (err != CL_SUCCESS) {
            printf("Error: Failed to create a device group!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    ocl.context = clCreateContext(0, 1, &ocl.device, NULL, NULL, &err);
    if (!ocl.context) {
        printf("Error: Failed to create a compute context!\n");
        exit(EXIT_FAILURE);
    }
    
    ocl.queue = clCreateCommandQueue(ocl.context, ocl.device, 0, &err);
    if (!ocl.queue) {
        printf("Error: Failed to create a command queue!\n");
        clReleaseContext(ocl.context);
        exit(EXIT_FAILURE);
    }
    
    ocl.program = clCreateProgramWithSource(ocl.context, 1, &kernelSource, NULL, &err);
    if (!ocl.program) {
        printf("Error: Failed to create compute program!\n");
        exit(EXIT_FAILURE);
    }
    
    err = clBuildProgram(ocl.program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];
        clGetProgramBuildInfo(ocl.program, ocl.device, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
        printf("Build Log:\n%s\n", buffer);
        exit(EXIT_FAILURE);
    }
    
    ocl.kernel = clCreateKernel(ocl.program, "convolution", &err);
    if (!ocl.kernel || err != CL_SUCCESS) {
        printf("Error: Failed to create compute kernel!\n");
        exit(EXIT_FAILURE);
    }
    
    err  = clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem), NULL);
    err |= clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem), NULL);
    err |= clSetKernelArg(ocl.kernel, 2, sizeof(int), &width);
    err |= clSetKernelArg(ocl.kernel, 3, sizeof(int), &height);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to set kernel arguments! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    return ocl;
}

///////////////////////////////////////////////////////////////////////////////
///                   OpenCL Execution                                    /////
/// Steps:                                                                /////
/// 1. Set kernel arguments                                               /////
/// 2. Launch the kernel                                                  /////
/// 3. Read the output buffer                                             /////
///////////////////////////////////////////////////////////////////////////////

void executeKernel(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, int width, int height) {
    cl_int err;
    err  = clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem), &inputBuffer);
    err |= clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem), &outputBuffer);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to set kernel buffer arguments! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    size_t globalWorkSize[2] = { (size_t)width, (size_t)height };
    size_t localWorkSize[2] = {16, 16};
    
    err = clEnqueueNDRangeKernel(ocl.queue, ocl.kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to execute kernel! %d\n", err);
        exit(EXIT_FAILURE);
    }
    clFinish(ocl.queue);
}

void cleanup(OpenCLObjects ocl, unsigned char *image, float *outputImage, float *inputImage) {
    clReleaseKernel(ocl.kernel);
    clReleaseProgram(ocl.program);
    clReleaseCommandQueue(ocl.queue);
    clReleaseContext(ocl.context);
    
    stbi_image_free(image);
    free(inputImage);
    free(outputImage);
}


///////////////////////////////////////////////////////////////////////////////
///                   Main Function                                       /////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <folder_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int count;
    char **files = list_image_files(argv[1], &count);

    if (!files) {
        fprintf(stderr, "No image files found or error reading directory.\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %d image files:\n", count);
    
    int width, height, channels;
    unsigned char *image = loadImage(files[0], &width, &height, &channels);

    OpenCLObjects ocl = initOpenCL(kernelSource, width, height);

    size_t img_size = width * height;
    float *inputImage = (float *)malloc(img_size * sizeof(float));
    float *outputImage = (float *)malloc(img_size * sizeof(float));

    cl_int err;
    cl_mem inputBuffer = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, img_size * sizeof(float), inputImage, &err);
    cl_mem outputBuffer = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, img_size * sizeof(float), NULL, &err);


    clock_t start = clock();
    for (int i = 0; i < count; i++) {
        // printf("%d/%d File : %s\n",i, count, files[i]);
        
        unsigned char *image = loadImage(files[i], &width, &height, &channels);
        if (!image) {
            return EXIT_FAILURE;
        }
                
        convertImageToFloat(image, inputImage, img_size);

        printf("Processing time (convertImageToFloat) : %f ms\n", ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0);
            
        clEnqueueWriteBuffer(ocl.queue, inputBuffer, CL_FALSE, 0, img_size * sizeof(float), inputImage, 0, NULL, NULL);

        printf("Processing time (clEnqueueWriteBuffer) : %f ms\n", ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0);

        executeKernel(ocl, inputBuffer, outputBuffer, width, height);

        printf("Processing time (executeKernel) : %f ms\n", ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0);

        clEnqueueReadBuffer(ocl.queue, outputBuffer, CL_FALSE, 0, img_size * sizeof(float), outputImage, 0, NULL, NULL);
        clFinish(ocl.queue);

        printf("Processing time (clEnqueueReadBuffer) : %f ms\n", ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0);

        char output_file[1024];
        snprintf(output_file, sizeof(output_file), "output/opencl/%s", files[i]);
        saveOutputImage(output_file, outputImage, width, height);
        
        printf("Processing time (saveOutputImage) : %f ms\n", ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000.0);

        free(files[i]);
    }
    cleanup(ocl, image, outputImage, inputImage);
    free(files);

    clock_t end = clock();
    printf("Execution Time: %f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);

    return 0;
}
