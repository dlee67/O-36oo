/*

	For this source, locks are done through the System V semaphors.

	08:16PM 

	It was a wrong decision because semaphor actually LOCKS the process,

	instread of prevensting time sharing.

	If that's the case, maybe it might be a good idea to go back on the
		
	homework 2, and make some adjustments so that the signaling happens

	properly.

*/
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <errno.h>
#include <iostream>

using namespace std;

union semun{

	int val;

	struct semid_ds* buf;

	unsigned short* array;

	struct seminfo* __buf;

};

static int globalVar = 0;

//static struct sembuf sop;

//static int semid = semget(IPC_PRIVATE, 1, 0777);

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadFunction(void* arg){

	struct sembuf sop;

	int semid = semget(IPC_PRIVATE, 1, 0777);

	sop.sem_op = -1;
	sop.sem_num = 0;
	sop.sem_flg = 0;

	semop(semid, &sop, 1);

	int local = 0;

	int x;

	for(x = 0; x < 100000000; x++){

		cout << "It's iterating" << endl;

//		pthread_mutex_lock(&mutex);
	
		local = globalVar;
	
		local++;

		globalVar = local;

//		pthread_mutex_unlock(&mutex);

	}

	sop.sem_op = 1;

	semop(semid, &sop, 1);	

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
