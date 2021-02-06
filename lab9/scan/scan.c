#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char * argv[])
{
    int rank;
    int procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Status stat;
    int a[10] = {5, 4, 1, 6, 3, 5, 0, 1, 8, 5};
    int b = 0;
    int c;
    for (int step = 1; step < procs; step *= 2) {
        c = a[rank];
        
        if (rank >= step) {

            MPI_Recv(&b, 1, MPI_INT, rank - step, 1, MPI_COMM_WORLD, &stat);
            a[rank] += b;
        }
        if (rank < procs - step) {
            MPI_Send(&c, 1, MPI_INT, rank + step, 1, MPI_COMM_WORLD);

        }
    }
    /*for(int i=0; i < procs; i++){
	printf("%d ", a[i]);
    }
    printf("\n");*/
    printf("Hello from %i/%i, with value a[%d] = %i\n"
       ,rank, procs, rank, a[rank]);
    MPI_Finalize();
    return 0;
}
