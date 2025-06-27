const char* kernelSource = 
 __kernel void convolution(__global float* input, __global float* output, int width, int height) {
     int x = get_global_id(0);
     int y = get_global_id(1);
     int offset = 1; // For a 3x3 kernel 
     if (x >= offset && x < (width - offset) && y >= offset && y < (height - offset)) {
         float sum = 0.0f;
         for (int ky = 0; ky < 3; ky++) {
             for (int kx = 0; kx < 3; kx++) {
                 int pixel_x = x + kx - offset;
                 int pixel_y = y + ky - offset;
                 float pixel = input[pixel_y * width + pixel_x];
                 float kvalue = (kx == 0) ? 1.0f : ((kx == 1) ? 0.0f : -1.0f);
                 sum += pixel * kvalue;
             }
         }
         output[y * width + x] = sum;
    }
}