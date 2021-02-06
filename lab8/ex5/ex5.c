#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROOT 0
MPI_Status status;

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    // Checks the number of processes allowed.
    if (numtasks != 2) {
        printf("Wrong number of processes. Only 2 allowed!\n");
        MPI_Finalize();
        return 0;
    }

    // How many numbers will be sent.
    int send_numbers = 10;
    int value, tag;

    if (rank == 0) {
	// Generate the random numbers.
        // Generate the random tags.
        // Sends the numbers with the tags to the second process.
	srand(time(0));
	for(int i = 0; i < send_numbers; i++){
		value = rand() % 50;
		tag = rand() % 10;
		MPI_Send(&value, 1, MPI_INT,1 ,tag, MPI_COMM_WORLD);
	}
        
    } else {
	// Receives the information from the first process.
        // Prints the numbers with their corresponding tags.
	MPI_Recv(&value, 1, MPI_INT, MPI_ANY_SOURCE, 1 , MPI_COMM_WORLD, &status);
	printf("number  = %d, tag = %d\n", value, tag);

    }

    MPI_Finalize();

}

