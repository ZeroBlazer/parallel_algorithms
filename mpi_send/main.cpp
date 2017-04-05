#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */

const int LIMIT = 5;

int main(void) {
    // char       greeting[MAX_STRING];
    // int        my_rank, p, q;

    int        my_rank, p;

    /* Start up MPI */
    MPI_Init(NULL, NULL);

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(p != 2) {
        printf("You should run this program with only two processes\n");
        return 0;
    }

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int counter = 0,
        othr_prank = !my_rank;

    while(counter < LIMIT) {
        if(my_rank == counter % 2) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, othr_prank, 0,
                     MPI_COMM_WORLD);
            printf(">> P%d sent %d to P%d\n", my_rank, counter, othr_prank);
        }
        else {
            MPI_Recv(&counter, 1, MPI_INT, othr_prank, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("<< P%d received %d from P%d\n", my_rank, counter, othr_prank);
        }
    }

    // if (my_rank == 0) {
    //     printf("Greetings from process %d of %d\n", my_rank, p);
    //     for (q = 1; q < p; q++) {
    //        MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 
    //           0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //        printf("%s\n", greeting);
    //     } 
    // } else {
    //     sprintf(greeting, "Greetings from process %d of %d", 
    //           my_rank, p);
    //     MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,
    //           MPI_COMM_WORLD);
    // }

   /* Shut down MPI */
   MPI_Finalize();
   return 0;
}