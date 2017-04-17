#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void pi_calculation(size_t thread_count);

void* Thread_sum(void* rank);