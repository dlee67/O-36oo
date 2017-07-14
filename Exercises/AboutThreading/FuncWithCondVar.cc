/*

	To understand this code, I need to be aware that this WILL NOT EXECUTE things SEQUENTIALLY.

	After the child thread starts, parent threads coninues to execute next instructions immdiately.

*/
#include <pthread.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int done = 0;

static pthread_cond_t indicator = PTHREAD_COND_INITIALIZER;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//wait is used when I want a particular thread to sleeee..    .
//pthread_cond_wait(pthread_cond_t *indicator, pthread_mutex_t *m);

//signal is used when thread has to change a course of logic.
//pthread_cond_signal(pthread_cond_t *indicator)

void thr_exit(){

	pthread_mutex_lock(&mutex);

	done = 1;

	/*

		The line below tell to C++ that, "there must be a thread with the indicator(which is called restrict_condition officially)

		that has been just passed in. Please, go find it and remove it's lock."

	*/
	pthread_cond_signal(&indicator);
	
	pthread_mutex_unlock(&mutex);	

}

void *child(void *arg){

	printf("Child will go into sleep.\n");

	sleep(5);

	printf("Child has woken up\n");
	thr_exit();
	return NULL;

}

void thr_wait_to_join(){

	printf("Parent will now wait for the child.\n");

	pthread_mutex_lock(&mutex);

	while(done == 0){

		//Wait realseases the mutex lock, which requires mutex to be passed in.
		//Fun part about this line of code is that when the line below is called
		//after the pthread_signal was called, then the thread will not be able to be
		//woken up.
		/*
		
			Now, to actually analyze what's happening with the line below,
			
			I am telling the compiler to unlock the particular mutex I've just passed in;

			however, until the indicator "signals" this thread to proceed, it will

			remain in suspension.

			Since, the done variable is static(which means it's visible to all memory?),

			the done will be able to be assigned with new value, and be visible from the calling thread.

		*/	
		pthread_cond_wait(&indicator, &mutex);

	}

	pthread_mutex_unlock(&mutex);

}

int main(int argc, char** argv){

	printf("Parent: begin\n");

	pthread_t p;

	pthread_create(&p, NULL, child, NULL);

	thr_wait_to_join();

	printf("Parent: end\n");

	return 0;

}

