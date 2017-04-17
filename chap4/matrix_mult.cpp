#include "matrix_mult.h"

extern int thread_count,
    m,
    n;
extern pthread_t* thread_handles;
extern double start, finish, elapsed;

mat_type *A;
mat_type *x;
mat_type *y;

void matrix_multiplication(size_t thrd_cnt) {
    // mat_type start, finish, loc_elapsed, elapsed;
    thread_count = thrd_cnt;
    printf("> Multiplicación Matriz[m][n] y vector[n], Ingrese m y n: ");
    scanf("%d%d", &m, &n);

    mem_allocate(A, x, y, m, n);

    Generate_matrix(A, m, n);
    Generate_vector(x, n);

    thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));

    /*************TIMING*****************/
    start = clock();
    /************************************/

    for(int thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void*)thread);

    for(int thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    /*************TIMING*****************/
    finish = clock();
    /************************************/

    // printf("Result: \n"); Print_vector(y, m);

    free(A);    free(x);    free(y);

    /*************TIMING*****************/
    elapsed = (finish - start)/CLOCKS_PER_SEC;
    printf("Elapsed time = %e seconds\n", elapsed);
    /************************************/
}

void mem_allocate(mat_type* &A, mat_type* &x, mat_type* &y, int m, int n) {
    A = (mat_type*) malloc(m * n * sizeof(mat_type));
    x = (mat_type*) malloc(n * sizeof(mat_type));
    y = (mat_type*) malloc(m * sizeof(mat_type));
}

void Generate_matrix(mat_type A[], int m, int n) {
    for(register int i = 0; i < m; i++)
        for(register int j = 0; j < n; j++)
            A[i * n + j] = ((mat_type)random()) / ((mat_type)RAND_MAX);
}

void Generate_vector(mat_type X[], int m, int n) {
    for(register int i = 0; i < m; i++)
        for(register int j = 0; j < n; j++)
            X[i * n + j] = ((mat_type)random()) / ((mat_type)RAND_MAX);
}

void Generate_vector(mat_type x[], int n) {
    for(register int i = 0; i < n; i++)
        x[i] = ((mat_type)random()) / ((mat_type)RAND_MAX);
}

void Print_matrix(mat_type A[], int m, int n) {
    for(register int i = 0; i < m; i++) {
        for(register int j = 0; j < n; j++)
            printf("%4.1f ", A[i * n + j]);
        printf("\n");
    }
}

void Print_vector(mat_type X[], int m) {
    for(register int i = 0; i < m; i++) {
        printf("%4.1f ", A[i]);
    }
    printf("\n");
}

void* Pth_mat_vect(void* rank) {
    long my_rank = (long)rank;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    for(register int i = my_first_row; i <= my_last_row; i++) {
      y[i] = 0.0;
      for(register int j = 0; j < n; j++)
        y[i] += A[i * n + j] * x[j];
    }
    return NULL;
}