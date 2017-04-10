#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

void Mat_vect_mult(
        double local_A[] /* in  */ ,
        double local_x[] /* in  */ ,
        double local_y[] /* out */ ,
        int local_m /* in  */ ,
        int n /* in  */ ,
        int local_n /* in  */ ,
        MPI_Comm comm /* in  */ );
