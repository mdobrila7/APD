#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define ROOT 0

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    // Root process generates a random number.
    // Broadcasts to all processes.
    int random_num = 0;

    if (rank == 0) {
	srand(42);
        random_num = rand();
    }

    MPI_Bcast(&random_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process [%d], after broadcast %d.\n", rank, random_num);

    MPI_Finalize();

}

