#include <stdio.h>
#include <mpi.h>
#include "trapezoidal.h"
#include "distribution.h"

enum executer {
    trapezoid,
    distribut,
    matrix_ml,
    sorting
};

int main(int argc, char** argv) {
    executer exec =
        // trapezoid;
        distribut;
        // matrix_ml;
        // sorting;

    switch (exec) {
    case trapezoid:
        trapezoidal();
        break;
    case distribut:
        distribution(100);
        break;
    case matrix_ml:
        trapezoidal();
        break;
    case sorting:
        trapezoidal();
        break;
    default:
        printf("Nothing to execute :(");
        break;
    }
    
    return 0;
}