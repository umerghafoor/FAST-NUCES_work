#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h> // AVX intrinsics (x86)
// #include <arm_neon.h> // NEON intrinsics (Apple Silicon)

#define N 16384

void scalar_2Dimplementation(float A[N][N], float B[N][N], float C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[j][i] * B[i][j];
        }
    }
}

void scalar_1Dimplementation(float *A, float *B, float *C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = A[j * N + i] * B[i * N + j]; 
        }
    }
}

void simd_implementation(float *A, float *B, float *C) {
    for (int i = 0; i < N; i++) {
        int j;
        for (j = 0; j <= N - 8; j += 8) {
            __m256 a_vec = _mm256_load_ps(&A[i * N + j]);  
            __m256 b_vec = _mm256_load_ps(&B[i * N + j]);  
            __m256 c_vec = _mm256_mul_ps(a_vec, b_vec);  
            _mm256_store_ps(&C[i * N + j], c_vec);
        }
        // Handling remaining elements
        for (; j < N; j++) {
            C[i * N + j] = A[i * N + j] * B[i * N + j];
        }
    }
}

int main() {

    float *A, *B, *C;
    if (posix_memalign((void**)&A, 32, N * N * sizeof(float)) ||
        posix_memalign((void**)&B, 32, N * N * sizeof(float)) ||
        posix_memalign((void**)&C, 32, N * N * sizeof(float))) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < N * N; i++) {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }

    // Measure performance of scalar 2D implementation
    clock_t start = clock();
    scalar_2Dimplementation((float (*)[N])A, (float (*)[N])B, (float (*)[N])C);
    clock_t end = clock();
    printf("Scalar 2D time (Seconds): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Measure performance of scalar 1D implementation
    start = clock();
    scalar_1Dimplementation(A, B, C);
    end = clock();
    printf("Scalar 1D time (Seconds): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Measure performance of SIMD implementation
    start = clock();
    simd_implementation(A, B, C);
    end = clock();
    printf("SIMD time (Seconds): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}
