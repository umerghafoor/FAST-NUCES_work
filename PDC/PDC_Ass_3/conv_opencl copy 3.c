#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CL/cl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Structure to hold OpenCL objects.
typedef struct {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
} OpenCLObjects;

// Function prototypes
unsigned char* loadImage(const char *filename, int *width, int *height, int *channels);
void convertImageToFloat(unsigned char *image, float *floatImage, int size);
OpenCLObjects initOpenCL(const char *kernelSource, int width, int height);
void executeKernel(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, int width, int height);
void saveOutputImage(const char *filename, float *outputImage, int width, int height);
void cleanup(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, 
             unsigned char *image, float *outputImage, float *inputImage, unsigned char *outputImageUchar);

int main() {
    int width, height, channels;
    unsigned char *image = loadImage("input.jpeg", &width, &height, &channels);
    if (!image) {
        return EXIT_FAILURE;
    }
    
    size_t img_size = width * height;
    float *inputImage = (float *)malloc(img_size * sizeof(float));
    float *outputImage = (float *)malloc(img_size * sizeof(float));
    
    convertImageToFloat(image, inputImage, img_size);
    
    // OpenCL kernel source for vertical edge detection
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
    
    OpenCLObjects ocl = initOpenCL(kernelSource, width, height);
    
    clock_t start = clock();
    // Create buffers for input and output images
    cl_int err;
    cl_mem inputBuffer = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, img_size * sizeof(float), inputImage, &err);
    cl_mem outputBuffer = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, img_size * sizeof(float), NULL, &err);
    
    executeKernel(ocl, inputBuffer, outputBuffer, width, height);
    clock_t end = clock();
    
    printf("Execution Time: %f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
    
    // Read back the results
    err = clEnqueueReadBuffer(ocl.queue, outputBuffer, CL_TRUE, 0, img_size * sizeof(float), outputImage, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to read output array! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    saveOutputImage("output_opencl.png", outputImage, width, height);
    
    // Cleanup resources
    unsigned char *outputImageUchar = NULL; // if needed for further processing, otherwise pass NULL.
    cleanup(ocl, inputBuffer, outputBuffer, image, outputImage, inputImage, outputImageUchar);
    return 0;
}

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

OpenCLObjects initOpenCL(const char *kernelSource, int width, int height) {
    OpenCLObjects ocl;
    cl_int err;
    
    // Get platform and device
    err = clGetPlatformIDs(1, &ocl.platform, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to find an OpenCL platform!\n");
        exit(EXIT_FAILURE);
    }
    
    err = clGetDeviceIDs(ocl.platform, CL_DEVICE_TYPE_DEFAULT, 1, &ocl.device, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to create a device group!\n");
        exit(EXIT_FAILURE);
    }
    
    // Create context and command queue
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
    
    // Create program and build it
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
    
    // Create kernel
    ocl.kernel = clCreateKernel(ocl.program, "convolution", &err);
    if (!ocl.kernel || err != CL_SUCCESS) {
        printf("Error: Failed to create compute kernel!\n");
        exit(EXIT_FAILURE);
    }
    
    // Set kernel arguments that don't change
    err  = clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem), NULL); // to be set later
    err |= clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem), NULL); // to be set later
    err |= clSetKernelArg(ocl.kernel, 2, sizeof(int), &width);
    err |= clSetKernelArg(ocl.kernel, 3, sizeof(int), &height);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to set kernel arguments! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    return ocl;
}

void executeKernel(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, int width, int height) {
    cl_int err;
    // Reset kernel arguments that depend on buffers
    err  = clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem), &inputBuffer);
    err |= clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem), &outputBuffer);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to set kernel buffer arguments! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    size_t globalWorkSize[2] = { (size_t)width, (size_t)height };
    size_t localWorkSize[2] = {4, 4};
    
    // Start timing and launch the kernel
    clock_t start = clock();
    err = clEnqueueNDRangeKernel(ocl.queue, ocl.kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to execute kernel! %d\n", err);
        exit(EXIT_FAILURE);
    }
    clFinish(ocl.queue);
    clock_t end = clock();
}

void saveOutputImage(const char *filename, float *outputImage, int width, int height) {
    size_t img_size = width * height;
    unsigned char *outputImageUchar = (unsigned char *)malloc(img_size);
    // Convert float image back to unsigned char
    for (size_t i = 0; i < img_size; i++) {
        outputImageUchar[i] = (unsigned char)(outputImage[i] * 255.0f);
    }
    stbi_write_png(filename, width, height, 1, outputImageUchar, width);
    printf("Edge detection completed and saved as %s\n", filename);
    free(outputImageUchar);
}

void cleanup(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, 
             unsigned char *image, float *outputImage, float *inputImage, unsigned char *outputImageUchar) {
    clReleaseKernel(ocl.kernel);
    clReleaseProgram(ocl.program);
    clReleaseMemObject(inputBuffer);
    clReleaseMemObject(outputBuffer);
    clReleaseCommandQueue(ocl.queue);
    clReleaseContext(ocl.context);
    
    stbi_image_free(image);
    free(inputImage);
    free(outputImage);
    if (outputImageUchar) {
        free(outputImageUchar);
    }
}
