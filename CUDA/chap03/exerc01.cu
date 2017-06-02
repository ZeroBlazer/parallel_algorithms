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

__global__
void mtrx_sum_elem(float* C, float* A, float* B, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < N && col < N) {
        C[row * N + col] = A[row * N + col] + B[row * N + col];
    }
}

__global__
void mtrx_sum_row(float* C, float* A, float* B, int N) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;

    if(id < N) {
        for(int i = 0; i < N; ++i) {
            C[id * N + i] = A[id * N + i] + B[id * N + i];
        }
    }
}

// __global__
// void mtrx_sum_column(float* C, float* A, float* B, int N) {
//     int i = blockIdx.x * blockDim.x + threadIdx.x;

// }

__host__
void print_matrix(float* M, int N) {
    printf("============================================\n");
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("%.4f\t", M[i * N + j]);
        }
        printf("\n");
    }
    printf("============================================\n\n");
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
/*******************************************************/
    dim3 threadsPerBlock(N, N);
    dim3 blocksPerGrid(1, 1);
    if (N*N > 512) {
        threadsPerBlock.x = 512;
        threadsPerBlock.y = 512;
        blocksPerGrid.x = ceil(double(N)/double(threadsPerBlock.x));
        blocksPerGrid.y = ceil(double(N)/double(threadsPerBlock.y));
    }
/****************FILLING RANDOM MATRIX******************/    
    rand_matrix<<<blocksPerGrid, threadsPerBlock>>>(d_A, N);
    rand_matrix<<<blocksPerGrid, threadsPerBlock>>>(d_B, N);
    rand_matrix<<<blocksPerGrid, threadsPerBlock>>>(d_C, N);
/***************PRINTING RANDOM MATRICES****************/
    cudaMemcpy(A, d_A, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(B, d_B, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    print_matrix(A, N);
    print_matrix(B, N);
/*******************************************************/
    mtrx_sum_elem<<<blocksPerGrid, threadsPerBlock>>>(d_C, d_A, d_C, N);
    cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    print_matrix(C, N);
/*******************************************************/
    mtrx_sum_row<<<ceil(N * N / 512.0), 512>>>(d_C, d_A, d_C, N);
    cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    print_matrix(C, N);
/*******************************************************/
//     mtrx_sum_column<<<ceil(N/256.0), 256>>>(d_C, d_A, d_C, N);
//     cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);

//     print_matrix(C, N);
/*******************************************************/
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);
}