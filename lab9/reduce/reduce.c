#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
#define N 8

int main (int argc, char *argv[])
{
    int procs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat;
    int number;
    //int value = rank;
    int v[N] = {3, 5, 2, -7, 6, 1, 4, -8};
    int sum = v[rank];
    for (int i = 2; i <= procs; i *= 2) {
        // TODO
	if(rank % i == 0){
		
		MPI_Recv(&number, 1, MPI_INT, rank + i / 2, 1, MPI_COMM_WORLD, &stat);
		sum = sum + number;
	}
	else if (rank % (i / 2) == 0){
		MPI_Send(&sum, 1, MPI_INT, rank - i / 2, 1, MPI_COMM_WORLD);
	}
    }

    if (rank == 0) {
        printf("Result = %d\n", sum);
    }

    MPI_Finalize();

}

