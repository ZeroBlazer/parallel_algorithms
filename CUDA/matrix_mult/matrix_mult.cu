#include <stdio.h>
#include <curand.h>
#include <curand_kernel.h>

#define MAX 100
const int TILE_WIDTH = 16;

__global__
void rand_matrix(float* M, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < N && col < N) {
        // curandState_t state;
        // curand_init(0, 0, 0, &state);
        M[row * N + col] = (col + row * col) % MAX;//curand(&state) % MAX;
    }
}

__global__
void mtrx_mult(float* d_M, float* d_N, float* d_P, int Width) {
    __shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
    __shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

    int bx = blockIdx.x;    int by = blockIdx.y;
    int tx = threadIdx.x;   int ty = threadIdx.y;

    int Row = by * TILE_WIDTH + ty;
    int Col = bx * TILE_WIDTH + tx;

    float Pvalue = 0;
    
    for (int ph = 0; ph < Width / TILE_WIDTH; ++ph) {
        Mds[ty][tx] = d_M[Row * Width + ph * TILE_WIDTH + tx];
        Nds[ty][tx] = d_N[(ph * TILE_WIDTH + ty) * Width + Col];
        __syncthreads();

        for(int k = 0; k < TILE_WIDTH; ++k) {
            Pvalue += Mds[ty][k] * Nds[k][tx];
        }
        __syncthreads();
    }
    d_P[Row * Width + Col] = Pvalue;
}

__global__
void matrixMultiplicationKernel(float* A, float* B, float* C, int N) {
    int ROW = blockIdx.y*blockDim.y+threadIdx.y;
    int COL = blockIdx.x*blockDim.x+threadIdx.x;

    float tmpSum = 0;

    if (ROW < N && COL < N) {
        // each thread computes one element of the block sub-matrix
        for (int i = 0; i < N; i++) {
            tmpSum += A[ROW * N + i] * B[i * N + COL];
        }
    }
    C[ROW * N + COL] = tmpSum;
}

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
    int N = 16;  // int N = 1<<20;
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
    // rand_matrix<<<blocksPerGrid, threadsPerBlock>>>(d_C, N);
/***************PRINTING RANDOM MATRICES****************/
    cudaMemcpy(A, d_A, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(B, d_B, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // print_matrix(A, N);
    // print_matrix(B, N);
/*******************************************************/
    cudaEvent_t start, stop;
	float elapsedTime;
	cudaEventCreate(&start);
    cudaEventRecord(start,0);

    matrixMultiplicationKernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    
    cudaEventCreate(&stop);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start,stop);

    cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    // print_matrix(C, N);
    printf("N: %d ms\n", N);
    printf("SM Runtime : %f ms\n", elapsedTime);
/*******************************************************/
	cudaEventCreate(&start);
    cudaEventRecord(start,0);

    mtrx_mult<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    
    cudaEventCreate(&stop);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start,stop);

    cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    // print_matrix(C, N);
    printf("Runtime : %f ms\n", elapsedTime);
/*******************************************************/
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(A);
    free(B);
    free(C);
}