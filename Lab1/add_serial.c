#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    schelet pentru exercitiul 5
*/

#define N 4
#define NUM_THREADS 4
#define cores 4

int* arr;
int array_size;

void *f(void *arg) {
  	long ID = *(long*) arg;
  	int start = ID * (double)array_size / N;
	int end;
	if(((ID + 1) * (double)array_size / N) < array_size)
		end = (ID + 1) * (double)array_size / N;
	else end = array_size; 

	for (int i = start; i < end; i++) {
        arr[i] += 100;
    }

  	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
  	int r;
  	long id;
  	void *status;
  	long arguments[NUM_THREADS];    

	if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    // TODO: aceasta operatie va fi paralelizata
  	

  	for (id = 0; id < NUM_THREADS; id++) {
  		arguments[id] = id;
		r = pthread_create(&threads[id], NULL, f, &arguments[id]);

		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	for (id = 0; id < NUM_THREADS; id++) {
		r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

	for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
      }

  	pthread_exit(NULL);


}
