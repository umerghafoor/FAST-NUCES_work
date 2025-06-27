#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "conv_util.h"

unsigned char* loadImage(const char *filename, int *width, int *height, int *channels);
void convertImageToFloat(unsigned char *image, float *floatImage, int size);
void applyEdgeDetection(float *inputImage, float *outputImage, int width, int height);
void saveOutputImage(const char *filename, float *outputImage, int width, int height);

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
    
    clock_t start = clock();
    applyEdgeDetection(inputImage, outputImage, width, height);
    clock_t end = clock();
    
    printf("Execution Time: %f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);
    
    saveOutputImage("output_scalar.png", outputImage, width, height);
    
    stbi_image_free(image);
    free(inputImage);
    free(outputImage);
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

void applyEdgeDetection(float *inputImage, float *outputImage, int width, int height) {
    int offset = 1;
    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            float sum = 0.0f;
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixel_x = x + kx;
                    int pixel_y = y + ky;
                    float pixel = inputImage[pixel_y * width + pixel_x];
                    float kvalue = (kx == -1) ? 1.0f : ((kx == 0) ? 0.0f : -1.0f);
                    sum += pixel * kvalue;
                }
            }
            outputImage[y * width + x] = sum;
        }
    }
}

void saveOutputImage(const char *filename, float *outputImage, int width, int height) {
    size_t img_size = width * height;
    unsigned char *outputImageUchar = (unsigned char *)malloc(img_size);
    for (size_t i = 0; i < img_size; i++) {
        outputImageUchar[i] = (unsigned char)(outputImage[i] * 255.0f);
    }
    stbi_write_png(filename, width, height, 1, outputImageUchar, width);
    printf("Edge detection completed and saved as %s\n", filename);
    free(outputImageUchar);
}
