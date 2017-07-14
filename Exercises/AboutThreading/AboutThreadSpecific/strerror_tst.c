/*
	
	The problem with the linux interface book is that they have their own error handling functions(and many other category of the functions)
	where it is not present in the stereotypical libraries of C and C++...

	errEXITEN is one of them.

	At the same time, this example is the pure reason why flexing google muscle means more than anything else, for novice like me.

*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

//At the sametime, if they want to simulate the static variable being over written by
//other software entity, why didn't they do something like a line below?
static char *str;

static void* threadFunc(void* arg){

	//char *str;

	printf("Other thread about to call strerror()\n");

	str = strerror(EPERM);

	printf("Other thread: str (%p) = %s\n", str, str);

	return NULL;

}

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
