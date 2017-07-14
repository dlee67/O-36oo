/*

	Assigning a literal to a pointer could cause a seg fault.

*/
#define _GNU_SOURCE
#define MAX_ERROR_LEN 256

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static __thread char buf[MAX_ERROR_LEN];

static char* str;

static void* threadFunc(void* arg){

	printf("Other thread about to call strerror()\n");

	//Well, I am pretty sure whatever I've written down is not what they have intended, I better 
	//come back, and really drill my head in here.
	//str = strerror(EPERM);
	printf("Other thread: str (%p) = %s\n", str, strerror(EPERM));

	return NULL;

}

char* strerror(int err){

	if(err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL){
		snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err); 	
	}else{
		//The point is that since the var here is local to the thread,
		//it won't conflict with the data outside of this thread, and the caller.
		strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
		buf[MAX_ERROR_LEN - 1] = '\0';
	}

	return buf;

}

int main(int argc, char* argv[]){

	pthread_t t;

	int s;

	str = strerror(EINVAL);

	printf("Main thread has called strerror()\n");

	s = pthread_create(&t, NULL, threadFunc, NULL);
	/*
	They don't want to use things like perror for some reason.
	if(s != 0)
		errExitEN(s, "pthread_create");
	*/
	s = pthread_join(t, NULL);
	/*
	if(s != 0)
		errExitEN(s, "pthread_join");
	*/
	printf("Main thread: str (%p) = %s\n", str, str);

	exit(EXIT_SUCCESS);	
	
}
