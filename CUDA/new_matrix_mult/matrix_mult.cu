#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX 200;
#define TILE_WIDTH 32

__global__
void rand_matrix(float* M, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < N && col < N) {
        M[row * N + col] = (col + row * col) % MAX;
    }
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

__global__
void MatrixMulKernel(float* M, float* N, float* P,int Width) {
    __shared__ float ds_M[TILE_WIDTH][TILE_WIDTH];
    __shared__ float ds_N[TILE_WIDTH][TILE_WIDTH];
    __shared__ float ds_NN[TILE_WIDTH][TILE_WIDTH];
    
    int bx = blockIdx.x;
    int by = blockIdx.y;
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int Row = by * TILE_WIDTH + ty;
    int Col = bx * 2 * TILE_WIDTH + tx;

    float Pvalue = 0; float Pvalue2 = 0;
    // Loop over the M and N tiles required to compute the P element
    if((Row < Width) && (Col < Width)){
      for (int ph = 0; ph < Width/TILE_WIDTH; ++ph){

        // Collaborative loading of M and N tiles into shared memory
        ds_M[ty][tx] = M[Row * Width + ph * TILE_WIDTH + tx];    // ph = tile index
        ds_N[ty][tx] = N[(ph * TILE_WIDTH + ty) * Width + Col];
        ds_NN[ty][tx] = N[(ph * TILE_WIDTH + ty) * Width +(Col + TILE_WIDTH)];
        __syncthreads();

        for (int i = 0; i < TILE_WIDTH; ++i) {
            Pvalue += ds_M[ty][i] * ds_N[i][tx];
            Pvalue2 += ds_M[ty][i] * ds_NN[i][tx];
        }

        __syncthreads();
      }

      P[Row * Width + Col] = Pvalue;
      P[(Row * Width + Col) + TILE_WIDTH] = Pvalue2;
    }
}

void Mul_tiled(float *A, float *B, float *C, int N) {
    long long size = sizeof(float) * N * N;
    float *d_A,
          *d_B,
          *d_C;

    cudaMalloc((void **) &d_A, size);
    cudaMalloc((void **) &d_B, size);
    cudaMalloc((void **) &d_C, size);
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
/*******************************************************/
    dim3 dimGrid(ceil(N / TILE_WIDTH) / 2, ceil(N / TILE_WIDTH), 1);
    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
    
    cudaEvent_t start, stop;
	float elapsedTime;
	cudaEventCreate(&start);
    cudaEventRecord(start, 0);

    MatrixMulKernel<<<dimGrid,dimBlock>>>(d_A, d_B, d_C, N);
    
    cudaEventCreate(&stop);
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime, start,stop);

    cudaMemcpy(C, d_C, N * N * sizeof(float), cudaMemcpyDeviceToHost);
    // print_matrix(C, N);
    printf("N: %d\n", N);
    printf("SM Runtime : %f ms\n", elapsedTime);
    
    // Clean up:
    // cudaEventDestroy(start);
    // cudaEventDestroy(stop);
    
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}


int main(int argv, char ** argc) {
    long N = 1024;
    float *A,
          *B,
          *C;
    
    A = (float*)malloc(N * N * sizeof(float));
    B = (float*)malloc(N * N * sizeof(float));
    C = (float*)malloc(N * N * sizeof(float));

    for(long long i = 0; i < N * N; i++) {
        A[i] = 3;
        B[i] = 3;
    }

    Mul_tiled(A, B, C, N);
    // print_matrix(C, N);
    
    free(A);
    free(B);
    free(C);
}
