#include "matrix_mult.h"

void Mat_vect_mult(
        double local_A[] /* in  */ ,
        double local_x[] /* in  */ ,
        double local_y[] /* out */ ,
        int local_m /* in  */ ,
        int n /* in  */ ,
        int local_n /* in  */ ,
        MPI_Comm comm /* in  */ ) {
    double * x;
    int local_i, j;

    x = (double*) malloc(n * sizeof(double));
    MPI_Allgather(local_x, local_n, MPI_DOUBLE,
        x, local_n, MPI_DOUBLE, comm);
    
    for (local_i = 0; local_i < local_m; local_i++) {
        local_y[local_i] = 0.0;
        for (j = 0; j < n; j++)
            local_y[local_i] += local_A[local_i * n + j] * x[j];
    }
    free(x);
}