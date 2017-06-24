#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/******************EXERCISES******************/
// 1. Use OpenMP to implement the parallel
// histogram program discussed in Chapter 2.

// 2. Suppose we toss darts randomly at a square
// dartboard, whose bullseye is at the origin,
// and whose sides are 2 feet in length. Suppose
// also that there’s a circle inscribed in the
// square dartboard. The radius of the circle is
// 1 foot, and it’s area is π square feet. If the
// points that are hit by the darts are uniformly
// distributed (and we always hit the square),
// then the number of darts that hit inside the
// circle should approximately satisfy the equation
// number in circle / total number of tosses = π / 4

// 3. Count sort

/*********************************************/
int find_bin(float data, float bin_maxes[], int bin_count, float min_meas) {

}

int main(int argc, char* argv[]) {
    int thread_count = strtol(argv[1], NULL, 10);

    int data_count = 20;
    float data[] = {1.3,2.9,0.4,0.3,1.3,4.4,1.7,0.4,3.2,0.3,4.9,2.4,3.1,4.4,3.9,0.4,4.2,4.5,4.9,0.9};
    int bin_count = 5;
    float bin_maxes[data_count],
          min_meas,
          max_meas;

    for(int i = 0; i < n; i++) {
        if(data[i] < min_m)
            min_meas = data[i];
        if(data[i] > bin_max)
            max_meas = data[i];
    }

    float bin_width = (max_meas − min_meas) / bin_count;

    for ( b = 0; b < bin_count ; b ++) {
        
        bin_maxes[b] = min_meas + bin_width * (b + 1);
    }

#pragma omp parallel num_threads(thread_count)
{
    #pragma omp parallel for schedule(auto)
    for(i = 0; i < data_count; ++i) {
        bin = find_bin(data[i], bin_maxes, bin_count, min_meas);
        bin_counts[bin]++;
    }    
}

    return 0;
}
