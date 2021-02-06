#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    srand(50);
    int number = rand();

    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number.
        // Send the number to the next process.
	MPI_Send(&number, 1, MPI_INT, (rank + 1) % numtasks, 0, MPI_COMM_WORLD);
        printf("Proces %d : am primit %d.\n", rank, number);

    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the first process.
	MPI_Recv(&number, 1, MPI_INT, (rank - 1) % numtasks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        number += 2;
        printf("Proces %d : am primit %d.\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 0 , 0, MPI_COMM_WORLD);

    } else {
        // Middle process.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the next process.
	MPI_Recv(&number, 1, MPI_INT, (rank - 1) % numtasks, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        number += 2;
        printf("Proces %d : am primit %d.\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, (rank + 1) % numtasks, 0, MPI_COMM_WORLD);

    }

    MPI_Finalize();

}


