#include <stdio.h>
#include <mpi.h>
#include "trapezoidal.h"
#include "distribution.h"
#include "matrix_mult.h"
#include "sorting.h"

// #define TRAPEZOIDAL
// #define DISTRIBUTION
#define MATRIX_MULT
// #define SORTING

int main(int argc, char** argv) { 
#ifdef TRAPEZOIDAL
    trapezoidal();
#endif

#ifdef TRAPEZOIDAL
    distribution(100);
#endif

#ifdef MATRIX_MULT
    matrix_multiplication(argc, argv);
#endif
    
#ifdef SORTING
//  <n> <g>
    sorting(argc, argv);
#endif

    return 0;
}