#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void count_sort(int a[], int n) {
    int i, j, count;
    int* temp = malloc(n * sizeof(int));
    
    #pragma omp parallel for shared(a, n, temp) private(i, j, count)
    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }

    #pragma omp parallel for shared(a, n, temp) private(i)
	for (i = 0; i < n; i++)
        a[i] = temp[i];
        
    free((int*) temp);
}

void print_v(int a[], int n) {
    int i;
	for (i = 0; i < n; i++)
        printf("%d, ", a[i]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Especify number of iterations and threads");
        return 0;
    }
    long long int n = atoi(argv[1]);
    long long int n_threads = atoi(argv[2]);

    int *a = malloc(n * sizeof(int));
    
#pragma omp parallel num_threads(n_threads) default (none) shared(a, n)
{
    int i;
    srandom((int)time(NULL) ^ omp_get_thread_num());
    #pragma omp for
    for(i = 0; i < n; i++)
        a[i] = (int) rand() % 99;
}

    count_sort(a, n);
    print_v(a, n);

    return 0;
}