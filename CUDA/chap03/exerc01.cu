#include <stdio.h>
#include <curand.h>
#include <curand_kernel.h>

#define MAX 100

__global__
void rand_matrix(float* M, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < N && col < N) {
        curandState_t state;
        curand_init(0, 0, 0, &state);
        M[row * N + col] = curand(&state) % MAX;
    }
}

// __global__
// void mtrx_sum_elem(float* C, float* A, float* B, int N) {
//     int row = blockIdx.y * blockDim.y + threadIdx.y;
//     int col = blockIdx.x * blockDim.x + threadIdx.x;

// }

// __global__
// void mtrx_sum_row(float* C, float* A, float* B, int N) {
//     int i = blockIdx.x * blockDim.x + threadIdx.x;

// }

// __global__
// void mtrx_sum_column(float* C, float* A, float* B, int N) {
//     int i = blockIdx.x * blockDim.x + threadIdx.x;

// }

__host__
void print_matrix(float* M, int N) {
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("%d\t", M[i * N + j]);
        }
        printf("\n");
    }
}

int main(void) {
    int N = 5;  // int N = 1<<20;
    float *A,
          *B,
          *C,
          *d_A,
          *d_B,
          *d_C;
    
    A = (float*)malloc(N * N * sizeof(float));
    B = (float*)malloc(N * N * sizeof(float));
    C = (float*)malloc(N * N * sizeof(float));

    cudaMalloc(&d_A, N * N * sizeof(float));
    cudaMalloc(&d_B, N * N * sizeof(float));
    cudaMalloc(&d_C, N * N * sizeof(float));
/****************FILLING RANDOM MATRIX******************/    
    rand_matrix<<<ceil(N/256.0), 256>>>(d_A, N);
    rand_matrix<<<ceil(N/256.0), 256>>>(d_B, N);
    rand_matrix<<<ceil(N/256.0), 256>>>(d_C, N);
/***************PRINTING RANDOM MATRIX******************/
    cudaMemcpy(A, d_A, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(B, d_B, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    print_matrix(A, N);
    print_matrix(B, N);
/*******************************************************/
    
//   cudaMemcpy(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice);
//   cudaMemcpy(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice);

//   // Perform SAXPY on 1M elements
//   saxpy<<<(N+255)/256, 256>>>(N, 2.0f, d_x, d_y);

//   cudaMemcpy(y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost);

  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  free(A);
  free(B);
  free(C);
}