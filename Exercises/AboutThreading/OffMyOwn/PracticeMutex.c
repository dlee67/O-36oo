#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>

static int glob = 0;
//Just like the conditional variable, mutex must be innitialized as an object in the memory.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* coolThread(void* arg){

	int local = (int)arg;

	int x;

	for(x = 0; x < 1000000; x++){

		local = glob;
		local++;
		glob = local;

	}  

	return NULL;
	//return (void*)glob;

}

int main(int argc, char** argv){

	pthread_t t1, t2;

	//The examples are literally passing in something.
	int loop = 0;

	int* ret1, ret2;
	
	int errCheck1 = pthread_create(&t1, NULL, coolThread, &loop);

	if(errCheck1 != 0){

		perror("pthread_create");
		exit(EXIT_FAILURE);

	}
	
	int errCheck2 = pthread_create(&t2, NULL, coolThread, &loop);

	if(errCheck2 != 0){
	
		perror("pthread_create");
		exit(EXIT_FAILURE);	

	}

	int errCheck3 = pthread_join(t1, &ret1);

	if(errCheck3 != 0){

		perror("pthread_join");
		exit(EXIT_FAILURE);	

	}

	int errCheck4 = pthread_join(t2, &ret2);

	if(errCheck4 != 0){

		perror("pthread_join");
		exit(EXIT_FAILURE);

	}

	printf("Glob is: %d", glob);

	//printf("t1's return value is: %d", (int)((int*)ret1));
	//printf("t2's return value is: %d", (int)((int*)ret2)); 

}
