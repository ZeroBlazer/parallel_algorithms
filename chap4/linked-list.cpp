#include "linked-list.h"

extern int thread_count,
           n,
           m;
extern pthread_t* thread_handles;
extern double start, finish, elapsed;
double member_p, insert_p, delete_p;

#define ONEMUTEX
// #define MUTEXPERNODE
// #define RWLOCKS

struct list_node_s {
    int data;
    struct list_node_s* next;
#ifdef MUTEXPERNODE
    pthread_mutex_t mutex;
#endif
};

struct list_node_s *head_p = NULL;

#ifdef ONEMUTEX
    pthread_mutex_t list_mutex;
#endif

void linked_list_operations(size_t thrd_cnt) {
    printf("> Operaciones en una linked list, ingrese key_N, Ops_n, Member, Insert, Delete:\n");
    printf("Before allocating memory");

    thread_count = thrd_cnt;
    m = 1000;
    n = 100000;
    member_p = 99.9;
    insert_p = 0.05;
    delete_p = 0.05;

    thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));

    /*************INSERT KEYS*****************/
    printf("Before inserting random elements");
    for(int i = 0; i < n; i++) {	
		if(!Insert(rand()%54321))
			i--;
    }
    printf("After inserting random elements");
    /*****************************************/

#ifdef ONEMUTEX
    pthread_mutex_init(&list_mutex, NULL);
#endif

    /*************TIMING*****************/
    start = clock();
    /************************************/

    for(int thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread], NULL, operations, (void*)thread);

    for(int thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);

    /*************TIMING*****************/
    finish = clock();
    /************************************/

#ifdef ONEMUTEX
    pthread_mutex_destroy(&list_mutex);
#endif

    /*************TIMING*****************/
    elapsed = (finish - start)/CLOCKS_PER_SEC;
    printf("Elapsed time = %e seconds\n", elapsed);
    /************************************/
}

void* operations(void* rank) {
    int local_m = m / thread_count,
        i;
    int member_count = 0,
        insert_count = 0,
        delete_count = 0;
    // int range_begin = my_rank * local_m;
    // int range_end = range_begin + local_m;
    for(i = 0; i < local_m; i++) {
        int r = rand()%65536;
        float prob = (rand() % 100 / 100.0);
        if(prob < member_p) {
            pthread_mutex_lock(&list_mutex);
            Member(r);
            pthread_mutex_unlock(&list_mutex);
            member_count++;
        } else if(prob < member_p + insert_p) {
            pthread_mutex_lock(&list_mutex);
            Insert(r);
            pthread_mutex_unlock(&list_mutex);
            insert_count++;
        } else {			
            pthread_mutex_lock(&list_mutex);
            Delete(r);
            pthread_mutex_unlock(&list_mutex);
            delete_count++;
        }
    }

    printf("[%d]>>MOps = %d, IOps = %d, DOps = %d\n", *((int*)rank), member_count, insert_count, delete_count);
    return NULL;
}

#ifdef ONEMUTEX
int Member(int value) {
    struct list_node_s* curr_p = head_p;

    while(curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}

int Insert(int value) {
    struct list_node_s* curr_p = head_p;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = (list_node_s*) malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL) /* New first node */
            head_p = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    } else { /* Value already in list */
        return 0;
    }
}

int Delete(int value) {
    struct list_node_s* curr_p = head_p;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) { /* Deleting first node in list */
            head_p = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    } else { /* Value isn’t in list */
        return 0;
    }
}
#endif

#ifdef MUTEXPERNODE
int Member(int value) {
    struct list_node_s* temp_p;
 
    pthread_mutex_lock(&head_p_mutex);
    temp_p = head_p;
    while(temp_p != NULL && temp_p->data < value) {
        if(temp_p->next != NULL)
            pthread_mutex_lock(&(temp_p->next->mutex));
        if (temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        pthread_mutex_unlock(&(temp_p->mutex));
        temp_p = temp_p->next;
    }
 
    if(temp_p == NULL || temp_p->data > value) {
        if (temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        if (temp_p != NULL)
            pthread_mutex_unlock(&(temp_p->mutex));
        return 0;
    } else {
        if (temp_p == head_p)
            pthread_mutex_unlock(&head_p_mutex);
        pthread_mutex_unlock(&(temp_p->mutex));
        return 1;
    }
}
#endif