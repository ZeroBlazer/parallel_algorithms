#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>

float *create_rand_nums(int num_elements);

float compute_avg(float *array, int num_elements);

void distribution(int n_elems_pp = 50);
