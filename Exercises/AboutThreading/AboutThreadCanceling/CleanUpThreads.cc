/*

	Don't really know why I would want to use things like thread cleaners; however, I should know more about them.

	At the sametime, there is this thing called asynchronous cancelability, and delved in depth in page 679, but

	I don't really know how to code any of these out of my head yet, nor I understand them enough so I can teach

	others about it.



	Also, starting from around page 682 or so, additional ideas about threads are discussed, such as an

	idea about how thread can send and receive signals.


	Surprisingly enough, starting from the page 685, the book discusses about how signals can be dealt with synchronously.


	From page 686, the book talks about how the threads behave when important functions such as fork() and exec() uses 

	threads.

	
	I have not read the further pages.

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

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static int glob = 0;

static void cleanupHandler(void* arg){

	int s;

	printf("cleanup: freeing block at %p\n", arg);

	free(arg);

	printf("cleanup: unlocking mutex\n");

	s = pthread_mutex_unlock(&mtx);

	if(s != 0){
		perror("pthread_mutex_unlock");
		exit(EXIT_FAILURE);	
	}

}

static void* threadFunc(void* arg){

	int s;

	void* buf = NULL;

	buf = malloc(0x10000);

	printf("thread: allocated memory at %p\n", buf);

	s = pthread_mutex_lock(&mtx);

	if(s != 0){
		perror("pthread_mutex_lock");
		exit(EXIT_FAILURE);	
	}

	pthread_cleanup_push(cleanupHandler, buf);

	while(glob == 0){
		s = pthread_cond_wait(&cond, &mtx);
		if(s != 0){
			perror("pthread_cond_wait");
			exit(EXIT_FAILURE);
		}
	}

	printf("thread: condition wait loop complete\n");
	pthread_cleanup_pop(1);
	return NULL;
	
}

int main(int argc, char** argv){

	pthread_t thr;

	void* res;

	int s;

	s = pthread_create(&thr, NULL, threadFunc, NULL);

	if(s != 0){
	
		perror("pthread_create");	
		exit(EXIT_FAILURE);	

	}

	sleep(2);

	if(argc == 1){

		printf("main: about to cancel thread\n");
		s = pthread_cancel(thr);
		if(s != 0){
			perror("pthread_cancel");
			exit(EXIT_FAILURE);		
		}

	}else{
	
		printf("main: about to signal condition variable\n");
		glob = 1;
		s = pthread_cond_signal(&cond);
		if(s != 0){
			perror("pthread_cond_signal");
			exit(EXIT_FAILURE);
		}	
	}

	s = pthread_join(thr, &res);

	if(s != 0){
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}

	if(res == PTHREAD_CANCELED){
		printf("main: thread was canceled\n");
	}else{
		printf("main: thread terminated normally\n");
	}

	exit(EXIT_SUCCESS);

}
