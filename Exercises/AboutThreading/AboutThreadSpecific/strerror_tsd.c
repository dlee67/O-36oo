#define _GNU_SOURCE
#define MAX_ERROR_LEN 256

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

static char* str;
static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_key_t strerrorKey;

static void* threadFunc(void* arg){

	//char *str;

	printf("Other thread about to call strerror()\n");

	str = strerror(EPERM);

	printf("Other thread: str (%p) = %s\n", str, str);

	return NULL;

}

static void destructor(void *buf){
	
	//If whatever passed in to this function was
	//already allocated, then the 
	//it is now deallocated.
	free(buf);

}

static void createKey(void){

	int s;

	s = pthread_key_create(&strerrorKey, destructor);

	if(s != 0)
		perror("pthread_key_create");

}
/*
	
	Seems like things are more clear now because 

	there is clear example of how thread specific data

	can be implemented.

	I mean, I took the source code of a library function,

	and directly adjusted things in it.

*/
char* strerror(int err){

	int s;
	char *buf;

	s = pthread_once(&once, createKey);
	
	if(s != 0)
		perror("pthread_once");		

	buf = pthread_getspecific(strerrorKey);
	if(buf == NULL){

		buf = malloc(MAX_ERROR_LEN);
		if(buf == NULL)
			exit(EXIT_FAILURE);		

		s = pthread_setspecific(strerrorKey, buf);
		if(s != 0)
			perror("pthread_setspecific");	

	}

	if(err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL){
		snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err); 	
	}else{
		strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
	}

	return buf;

}

//And I am guessing they want me to cpy paste the prev code.

int main(int argc, char* argv[]){

	pthread_t t;
	int s;

	//char *str;

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
