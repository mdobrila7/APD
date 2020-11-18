#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 



void *f1(void *arg) {
  	//long id = *(long*) arg;
  	printf("Sunt in f1\n");
  	pthread_exit(NULL);
}

void *f2(void *arg) {
  	//long id = *(long*) arg;
  	printf("Sunt in f2\n");
  	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	long NUM_THREADS = 1;	
	pthread_t threads[NUM_THREADS];
  	int r1,r2;
  	long id;
  	void *status;
  	long arguments[NUM_THREADS];
	


  		arguments[0] = 0;
		r1 = pthread_create(&threads[0], NULL, f1, &arguments[0]);
    		if (r1) {
              		printf("Eroare la crearea thread-ului 1\n");
              		exit(-1);
        	}
		arguments[1] = 1;
    		r2 = pthread_create(&threads[1], NULL, f2, &arguments[1]);
    		if (r2) {
              		printf("Eroare la crearea thread-ului 2\n");
              		exit(-1);
        	}


  	for (id = 0; id < NUM_THREADS; id++) {
		r1 = pthread_join(threads[0], &status);
    		if (r1) {
              		printf("Eroare la asteptarea thread-ului 1\n");
              		exit(-1);
        	}

    		r2 = pthread_join(threads[1], &status);
    		if (r2) {
              		printf("Eroare la asteptarea thread-ului 2\n");
              		exit(-1);
        	}
  	}

  	pthread_exit(NULL);
}
