#include "pi-calc.h"

int thread_count,
    n;
double sum;

void pi_calculation(size_t thrd_cnt) {
    thread_count = thrd_cnt;
    printf("> Cálculo del valor Pi, ingrese n: ");
    scanf("%i", &n);
}

