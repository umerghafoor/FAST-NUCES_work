#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <omp.h>

#define PI 3.14159265358979323846
#define WIDTH 1080
#define HEIGHT 1080

int TERMS;
int resolutions;

double normalize_angle(double x) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    return x;
}

double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int effective_terms(double x) {
    return fmin(TERMS, 15 + fabs(x) / 2);
}

double taylor_sin_parallel(double x) {
    double sum = 0.0;
    int n_terms = effective_terms(x);
    x = normalize_angle(x);
    
    #pragma omp parallel for schedule(static, 10) reduction(+:sum)
    for (int n = 0; n < n_terms; n++) {
        double term = pow(x, 2 * n + 1) / factorial(2 * n + 1);
        if (n % 2 != 0)
            term = -term;
        sum += term;
        // printf("this thread sin is %d\n", omp_get_thread_num());
    }
    return sum;
}

double taylor_cos_parallel(double x) {
    double sum = 0.0;
    int n_terms = effective_terms(x);
    x = normalize_angle(x);
    
    #pragma omp parallel for schedule(static, 10) reduction(+:sum)
    for (int n = 0; n < n_terms; n++) {
        double term = pow(x, 2 * n) / factorial(2 * n);
        if (n % 2 != 0)
            term = -term;
        sum += term;
        // printf("this thread cos is %d\n", omp_get_thread_num());
    }
    return sum;
}

void draw_circle(SDL_Renderer *renderer, int j, int k, int r) {
    double x[resolutions], y[resolutions];
    
    double start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (int t = 0; t < resolutions; t++) {
        double rad = t * PI / 180.0;
        x[t] = r * taylor_cos_parallel(rad) + j;
        y[t] = r * taylor_sin_parallel(rad) + k;
        // printf("this thread is %d\n", omp_get_thread_num());
    }
    
    double end_time = omp_get_wtime();
    printf("OpenMP Series Calculations Time: %f seconds\n", end_time - start_time);
    
    for (int t = 0; t < resolutions; t++) {
        SDL_RenderDrawPoint(renderer, (int)x[t], (int)y[t]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <terms> <resolution> <num_threads>\n", argv[0]);
        return 1;
    }

    TERMS = atoi(argv[1]);
    resolutions = atoi(argv[2]);
    int num_threads = atoi(argv[3]);

    omp_set_num_threads(num_threads);

    int j = WIDTH / 2; // Center X
    int k = HEIGHT / 2; // Center Y
    int r = 200; // Fixed radius

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("OpenMP Series Calculations Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    draw_circle(renderer, j, k, r);
    SDL_RenderPresent(renderer);
    
    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
