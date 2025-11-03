#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

struct thread_data {
	int thread_id;
	int sum;
	char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg) {
	struct thread_data *my_data;
	int taskid, sum;
	char *hello_msg;
	
	my_data = (struct thread_data *) threadarg;
	taskid = my_data->thread_id;
	sum = my_data->sum;
	hello_msg = my_data->message;
	
	printf("Thread ID: %d, Sum: %d, Message: %s\n", 
		   taskid, sum, hello_msg);
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	char *messages[NUM_THREADS] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4"};
	int rc, t;
	int sum = 0;

	for(t = 0; t < NUM_THREADS; t++) {
		sum += t;
		thread_data_array[t].thread_id = t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].message = messages[t];
		printf("Creating thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, 
						  (void *)&thread_data_array[t]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	// Esperar a que todos los hilos terminen
	for(t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}
	
	printf("All threads completed\n");
	pthread_exit(NULL);
}