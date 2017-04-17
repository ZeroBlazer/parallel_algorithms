#include "pi-calc.h"

// #define BUSYWAIT
#define MUTEX

extern int thread_count,
           n;
extern long flag;
extern pthread_t* thread_handles;
double sum;
pthread_mutex_t mutex;

void pi_calculation(size_t thrd_cnt) {
    thread_count = thrd_cnt;
    flag = 0;
    sum = 0.0;

    printf("> Cálculo del valor de Pi, ingrese n: ");
    scanf("%i", &n);

    thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));

#ifdef MUTEX
    pthread_mutex_init(&mutex, NULL);
#endif

    for(int thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*)thread);

    for(int thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

#ifdef MUTEX
    pthread_mutex_destroy(&mutex);
#endif

    sum *= 4.0;

    printf("Pi: %f\n", sum);
}

void* Thread_sum(void* rank) {
    long my_rank = (long)rank;
    double factor, my_sum = 0.0;
    long long i;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    
    if (my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    for(i = my_first_i; i < my_last_i; i++, factor = -factor)
        my_sum += factor / (2*i + 1);

#ifdef BUSYWAIT
    while(flag != my_rank);
    sum += my_sum;
    flag = (flag + 1) % thread_count;
#endif

#ifdef MUTEX
    pthread_mutex_lock(&mutex);
    sum += my_sum;
    pthread_mutex_unlock(&mutex);
#endif

    return NULL;
}