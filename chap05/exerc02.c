#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Especify number of iterations");
        return 0;
    }
    long long int n_iter = atoi(argv[1]);
    long long int n_threads = atoi(argv[2]);
    int i,
        count = 0;
    double x,
           y,
           z;

#pragma omp parallel for num_threads(n_threads) reduction(+:count) \
    default (none) private(i, x, y, z) shared(count, n_iter)
    for(i = 0; i < n_iter; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        z = (x * x) + (y * y);
        if (z<=1)
            ++count; 
    }

    double pi = 4.0 * ((double) count / (double) (n_iter * n_threads));
    printf("Pi: %f\n", pi);
    
    return 0;
}