/*
	Thread has something called cancelation point, and particular thread won't cancel, until

	the cancelation point is reached.

	pthread_testcancle is also a thing where if the calling thread is pending, then the thread gets safely

	canceled.

*/
#define _GNU_SOURCE
#define MAX_ERROR_LEN 256

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static void* threadFunc(void* arg){

	int j;

	printf("New thread started\n");
	for(j = 1; ; j++){
		printf("Loop %d\n", j);
		sleep(1);
	}

	return NULL;

}

int main(int argc, char** argv){

	pthread_t thr;

	int s;
		
	void* res;

	s = pthread_create(&thr, NULL, threadFunc, NULL);

	if(s != 0){

		perror("pthread_create");
		exit(EXIT_FAILURE);

	}
	
	sleep(3);

	/*

		Nothing really special, pthread_cancel really just stops the thread from doing anything.

	*/
	s = pthread_cancel(thr);

	if(s != 0){
		perror("pthread_cancle");
		exit(EXIT_FAILURE);		
	}
	
	/*

		It is directly stated in the man page that when the thread is canceled, retrival variable
	
		will have a macro assigned PTHREAD_CANCELED.

	*/
	s = pthread_join(thr, &res);

	if(res == PTHREAD_CANCELED){
	
		printf("Thread was canceled\n");

	}else{
		
		printf("Thread was not canceled");

	}

	exit(EXIT_SUCCESS);

}
