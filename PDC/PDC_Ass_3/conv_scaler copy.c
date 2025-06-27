#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "conv_util.h"

#define KERNEL_SIZE 3

float kernel[KERNEL_SIZE][KERNEL_SIZE] = {
    {1,  0, -1},
    {1,  0, -1},
    {1,  0, -1}
};

unsigned char* loadImage(const char *filename, int *width, int *height, int *channels) {
    unsigned char *img = stbi_load(filename, width, height, channels, 1);
    if (!img) {
        printf("Failed to load image: %s\n", filename);
    }
    return img;
}

void convertImageToFloat(const unsigned char *image, float *floatImage, int size) {
    for (int i = 0; i < size; i++) {
        floatImage[i] = (float)image[i] / 255.0f;
    }
}

void apply_convolution(float *input, float *output, int width, int height) {
    int offset = KERNEL_SIZE / 2;
    for (int y = offset; y < height - offset; y++) {
        for (int x = offset; x < width - offset; x++) {
            float sum = 0.0f;
            for (int ky = 0; ky < KERNEL_SIZE; ky++) {
                for (int kx = 0; kx < KERNEL_SIZE; kx++) {
                    int pixel_x = x + (kx - offset);
                    int pixel_y = y + (ky - offset);
                    sum += input[pixel_y * width + pixel_x] * kernel[ky][kx];
                }
            }
            output[y * width + x] = sum;
        }
    }
}

void saveImage(const char *filename, const float *output, int width, int height) {
    int img_size = width * height;
    unsigned char *output_image_uchar = (unsigned char *)malloc(img_size);
    for (int i = 0; i < img_size; i++) {
        output_image_uchar[i] = (unsigned char)(output[i] * 255.0f);
    }
    stbi_write_png(filename, width, height, 1, output_image_uchar, width);
    free(output_image_uchar);
}

void cleanup(unsigned char *image, float *inputImage, float *outputImage) {
    stbi_image_free(image);
    free(inputImage);
    free(outputImage);
}

float* doProcessing(int width, int height, unsigned char *image) {
    int img_size = width * height;
    float *input_image = (float *)malloc(img_size * sizeof(float));
    float *output_image = (float *)malloc(img_size * sizeof(float));

    convertImageToFloat(image, input_image, img_size);
    apply_convolution(input_image, output_image, width, height);

    cleanup(image, input_image, NULL);

    return output_image;
}

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

    clock_t start = clock();
    for (int i = 0; i < count; i++) {
        // printf("%d/%d File : %s\n",i, count, files[i]);

        int width, height, channels;
        unsigned char *image = loadImage(files[i], &width, &height, &channels);
        if (!image) {
            return EXIT_FAILURE;
        }

        float *output_image = doProcessing(width, height, image);
        
        char output_file[1024];
        snprintf(output_file, sizeof(output_file), "output/scaler/%s", files[i]);
        // printf("Output File : %s\n", output_file);
        saveImage(output_file, output_image, width, height);

        cleanup(NULL, NULL, output_image);

        free(files[i]);
    }
    free(files);

    clock_t end = clock();
    printf("Execution Time: %f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0);

    return 0;
}

