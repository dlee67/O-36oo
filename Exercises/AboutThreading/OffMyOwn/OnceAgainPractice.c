#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>

static int globalVar = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*

	The both treads seems like they arrive to same value 

	regardless.

	
	1000000

	The error was able to be caused in delibration after putting two more zeros.
	
	100000000.
	

	The moral of the story is, time slice occur in any given time of the process/thread; since,

	the time slice could occur out of no where, with the combination of TCB(which implies that each

	threads has their own stack), the unwanted value could update, delete, etc the intended value.

	
	Thus, we use techniques such as lock or mutex to keep that from happening.

*/
void* threadFunction(void* arg){

	int local = 0;

	int x;

	for(x = 0; x < 100000000; x++){

		pthread_mutex_lock(&mutex);
	
		local = globalVar;
	
		local++;

		globalVar = local;

		//I am guessing just having globalVar does not complicate the time sharing;
		//thus, the globalVar maintains the same value in both thread.

		pthread_mutex_unlock(&mutex);

	}

	return NULL;

}

int main(int argc, char** argv){

	pthread_t t1, t2;

	pthread_create(&t1, NULL, threadFunction, NULL);

	pthread_create(&t2, NULL, threadFunction, NULL);

	pthread_join(t1, NULL);
	
	pthread_join(t2, NULL);

	printf("Global is: %d", globalVar);

	return 0;

}
