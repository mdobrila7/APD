#include<mpi.h>
#include<stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define CONVERGENCE_COEF 10

static int num_neigh;
static int *neigh;

int leader, num_proc;
int visited = 0;
int* parents;

// citesc inputul
void read_neighbours(int rank) {
    FILE *fp;
    char file_name[15];
	sprintf(file_name, "./files/%d.in", rank);

    fp = fopen(file_name, "r");
	fscanf(fp, "%d", &num_neigh);

	neigh = malloc(sizeof(int) * num_neigh);

	for (size_t i = 0; i < num_neigh; i++)
		fscanf(fp, "%d", &neigh[i]);
}

// aleg liderul ca in laborator
int leader_chosing(int rank, int nProcesses) {
	int leader = -1;
	int q;
	leader = rank;
	
	for (int k = 0; k < CONVERGENCE_COEF; k++) {
		for (int i = 0; i < num_neigh; ++i) {
			MPI_Send(&leader, 1, MPI_INT, neigh[i], 1234, MPI_COMM_WORLD);
			int leader_neigh;
			MPI_Recv(&leader_neigh, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (leader_neigh < leader) {
				leader = leader_neigh;
			}
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	printf("%i/%i: leader is %i\n", rank, nProcesses, leader);

	return leader;
}

// realizez arborele de acoperire si compun vectorul de parinti ca in laborator
int* get_dst(int rank, int numProcs, int leader) {
	MPI_Status status;
	MPI_Request request;

	/* Vectori de parinti */
	int *v = malloc(sizeof(int) * numProcs);
	int *vRecv = malloc(sizeof(int) * numProcs);

	memset(v, -1, sizeof(int) * numProcs);
	memset(vRecv, -1, sizeof(int) * numProcs);
	
	if (rank == leader) {
		v[rank] = -1;
		for (int i = 0; i < num_neigh; ++i) {
			MPI_Send(v, numProcs, MPI_INT, neigh[i], 1235, MPI_COMM_WORLD);
		}

		for (int i = 0; i < num_neigh; ++i) {
			MPI_Recv(vRecv, numProcs, MPI_INT , neigh[i], MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (int j = 0; j < numProcs; ++j) {
				if (vRecv[j] != -1 && v[j] == -1) {
					v[j] = vRecv[j];
				}	
			}
			
		}

		for (int i = 0; i < num_neigh; ++i) {
			MPI_Send(v, numProcs, MPI_INT, neigh[i], 1235, MPI_COMM_WORLD);
		}

	} else {
		/* Daca procesul curent nu este liderul, inseamna ca va astepta un mesaj de la un parinte */
		MPI_Recv(v, numProcs, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		v[rank] = status.MPI_SOURCE;

		for (int i = 0; i < num_neigh; ++i) {
			if (neigh[i] != status.MPI_SOURCE) {
				MPI_Send(v, numProcs, MPI_INT, neigh[i], 1235, MPI_COMM_WORLD);
			}
		}

		for (int i = 0; i < num_neigh; ++i) {
			if (neigh[i] != status.MPI_SOURCE) {
				MPI_Recv(vRecv, numProcs, MPI_INT, neigh[i], MPI_ANY_TAG, MPI_COMM_WORLD , MPI_STATUS_IGNORE);
				for (int j = 0; j < numProcs; ++j) {
					if (vRecv[j] != -1 && v[j] == -1) {
						v[j] = vRecv[j];
					}
				}
			}
		}

		
		MPI_Send(v, numProcs, MPI_INT, status.MPI_SOURCE, 1235, MPI_COMM_WORLD);
		MPI_Recv(vRecv, numProcs, MPI_INT, status.MPI_SOURCE, 1235, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		for (int i = 0; i < numProcs; ++i) {
			if (vRecv[i] == rank) {
				MPI_Send(vRecv, numProcs, MPI_INT, i, 1235, MPI_COMM_WORLD);
			}
		}
	}

	for (int i = 0; i < numProcs && rank == leader; i++) {
		printf("The node %d has the parent %d\n", i, v[i]);
	}
	return v;
}

void bfs(int rank) {
    
    if (rank == leader) {
        // vizitez liderul
        visited = 1;

        // "vizitez" toti vecinii
        for (int i = 0; i < num_neigh; i++) {
            int val = 1;
            MPI_Send(&val, 1, MPI_INT, neigh[i], 1236, MPI_COMM_WORLD);
        }

        // trimit ack vecinilor ca si ei sa viziteze mai departe
        for (int i = 0; i < num_neigh; i++) {
            int val = 1;
            MPI_Send(&val, 1, MPI_INT, neigh[i], 1236, MPI_COMM_WORLD);
        }

        // astept sa primesc num_procs - 1 ack uri valide sau unul invalid, caz in care am gasit ciclu
        for (int i = 0; i < num_proc - 1; i++) {
            int exit_code;
            MPI_Recv(&exit_code, 1, MPI_INT , MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (exit_code == -1) {
                printf("ciclu\n");
                return;
            }
        }
        printf("Nu am gasit ciclu\n");
        
    } else {
        int val;

        // stiu ca am fost vizitat
        MPI_Recv(&val, 1, MPI_INT , parents[rank], MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // astept ack ul ca sa vizitez mai departe
        MPI_Recv(&val, 1, MPI_INT , parents[rank], MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // daca nodul era deja vizitat anunt liderul ca am gasit ciclu
        if (visited == 1) {
            int exit_code = -1;
            MPI_Send(&exit_code, leader, MPI_INT, leader, 1236, MPI_COMM_WORLD);

        // altfel trimit un ack normal la lider
        } else {
            int exit_code = 0;
            MPI_Send(&exit_code, leader, MPI_INT, leader, 1236, MPI_COMM_WORLD);
        }
        visited = 1;

        // "vizitez" toti vecinii cu exceptia parintelui
        for (int i = 0; i < num_neigh; i++) {
            if (parents[rank] != neigh[i]) {
                MPI_Send(&val, 1, MPI_INT, neigh[i], 1236, MPI_COMM_WORLD);
            }
        }

        // trimit ack vecinilor (cu exceptia parintelui) ca si ei sa viziteze mai departe
        for (int i = 0; i < num_neigh; i++) {
            if (parents[rank] != neigh[i]) {
                MPI_Send(&val, 1, MPI_INT, neigh[i], 1236, MPI_COMM_WORLD);
            }
        }
    }
}

int main(int argc, char * argv[]) {
	int rank, nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

	if (nProcesses != 8) {
		printf("please run with: mpirun --oversubscribe -np 8 %s\n", argv[0]);
		MPI_Finalize();	
		exit(0);
	}
	
	read_neighbours(rank);
	leader = leader_chosing(rank, nProcesses);

	MPI_Barrier(MPI_COMM_WORLD);
	parents = get_dst(rank, nProcesses, leader);

	MPI_Barrier(MPI_COMM_WORLD);
    bfs(rank);
    
    MPI_Finalize();
    return 0;
}