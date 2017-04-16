#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"

typedef double mat_type;

void mem_allocate(mat_type* &A, mat_type* &x, mat_type* &y, int m, int n);

void Generate_matrix(mat_type A[], int m, int n);

void Generate_vector(mat_type x[], int n);

void Print_matrix(mat_type A[], int m, int n);

void Print_vector(mat_type X[], int m);

void* Pth_mat_vect(void* rank);

void matrix_multiplication(size_t thread_count);