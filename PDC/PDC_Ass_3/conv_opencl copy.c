#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CL/cl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "conv_util.h"

#define KERNEL_FILE "conv_kernel.cl"

typedef struct {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
} OpenCLObjects;

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

void executeKernel(OpenCLObjects ocl, cl_mem inputBuffer, cl_mem outputBuffer, int width, int height) {
    cl_int err;
    err  = clSetKernelArg(ocl.kernel, 0, sizeof(cl_mem), &inputBuffer);
    err |= clSetKernelArg(ocl.kernel, 1, sizeof(cl_mem), &outputBuffer);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to set kernel buffer arguments! %d\n", err);
        exit(EXIT_FAILURE);
    }
    
    size_t globalWorkSize[2] = { (size_t)width, (size_t)height };
    size_t localWorkSize[2] = {4, 4};
    
    clock_t start = clock();
    err = clEnqueueNDRangeKernel(ocl.queue, ocl.kernel, 2, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to execute kernel! %d\n", err);
        exit(EXIT_FAILURE);
    }
    clFinish(ocl.queue);
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

char* readKernelSource(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open kernel file!\n");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    char *source = (char*)malloc(fileSize + 1);
    fread(source, 1, fileSize, file);
    source[fileSize] = '\0';
    fclose(file);
    return source;
}

float* doProcessing(int width, int height, unsigned char *image, OpenCLObjects *ocl, cl_mem inputBuffer, cl_mem outputBuffer)
{
    size_t img_size = width * height;
    float *inputImage = (float *)malloc(img_size * sizeof(float));
    float *outputImage = (float *)malloc(img_size * sizeof(float));

    convertImageToFloat(image, inputImage, img_size);

    cl_int err;
    err = clEnqueueWriteBuffer(ocl->queue, inputBuffer, CL_TRUE, 0, img_size * sizeof(float), inputImage, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Error: Failed to write input buffer!\n");
        exit(EXIT_FAILURE);
    }

    executeKernel(*ocl, inputBuffer, outputBuffer, width, height);
    
    err = clEnqueueReadBuffer(ocl->queue, outputBuffer, CL_TRUE, 0, img_size * sizeof(float), outputImage, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Error: Failed to read output array! %d\n", err);
        exit(EXIT_FAILURE);
    }

    free(inputImage);
    return outputImage;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <folder_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int count;
    char **files = NULL;
    files = list_image_files(argv[1], &count);

    if (!files) {
        fprintf(stderr, "No image files found or error reading directory.\n");
        return EXIT_FAILURE;
    }

    printf("Found %d image files:\n", count);

    clock_t start = clock();
    for (int i = 0; i < count; i++) {
        // printf("%d/%d File : %s\n",i, count, files[i]);
        int width, height, channels;
        unsigned char *image = loadImage(files[i], &width, &height, &channels);
        if (!image) {
            return EXIT_FAILURE;
        }

        char *kernelSource = readKernelSource(KERNEL_FILE);
        OpenCLObjects ocl = initOpenCL(kernelSource, width, height);
        free(kernelSource);

        size_t img_size = width * height;
        cl_int err;
        cl_mem inputBuffer = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY, img_size * sizeof(float), NULL, &err);
        cl_mem outputBuffer = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, img_size * sizeof(float), NULL, &err);
        
        float *output_image = doProcessing(width, height, image, &ocl, inputBuffer, outputBuffer);

        char output_file[1024];
        snprintf(output_file, sizeof(output_file), "output/opencl/%s", files[i]);
        // printf("Output File : %s\n", output_file);
        saveOutputImage(output_file, output_image, width, height);
        
        cleanup(ocl, inputBuffer, outputBuffer, image, output_image, NULL, NULL);
        free(files[i]);
    }
    free(files);

    clock_t end = clock();
    printf("Execution Time: %f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);

    return 0;
}
