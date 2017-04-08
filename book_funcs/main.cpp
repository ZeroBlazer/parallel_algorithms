#include <stdio.h>
#include <mpi.h>
#include "trapezoidal.h"
#include "distribution.h"

int main(int argc, char** argv) { 
    // trapezoidal();
    distribution(100);
    
    return 0;
}