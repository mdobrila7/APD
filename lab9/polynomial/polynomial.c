#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>



int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
        MPI_Status stat;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

		int polynomialSize;
		int n;
		int i;
		int j;
		float x;

		/*
			in fisierul de intrare formatul este urmatorul:
			numarul_de_coeficienti
			coeficient x^0
			coeficient x^1
			etc.
		*/

		FILE * polFunctionFile = fopen("a1.txt","rt");
		fscanf(polFunctionFile, "%i", &polynomialSize);

		/*
			in array-ul a se vor salva coeficientii ecuatiei / polinomului
			de exemplu: a = {1, 4, 4} => 1 * (x ^ 2) + 4 * (x ^ 1) + 4 * (x ^ 0)
		*/

		float *a = malloc(sizeof(float)*polynomialSize);
		for(i = 0; i < polynomialSize; i++) {
			fscanf(polFunctionFile, "%f", a + i);
			/*
				Se trimit coeficientii pentru x^1, x^2 etc. proceselor 1, 2 etc.
				Procesul 0 se ocupa de x^0 si are valoarea coeficientului lui x^0
			*/
		}
		fclose(polFunctionFile);

		for(x = 0; x < 5; x += 1) {
			float sum = 0;
			float xPowI = pow(x, rank);
			float recv;
			if (rank != 0)
				MPI_Recv(&sum, 1, MPI_FLOAT, rank - 1, 1, MPI_COMM_WORLD, &stat);
			sum += a[rank] * xPowI;
			if (rank == nProcesses - 1)
				printf("sum is %f\n", sum);
			if (rank != nProcesses - 1)
				MPI_Send(&sum, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
		}

	MPI_Finalize();
	return 0;
}
