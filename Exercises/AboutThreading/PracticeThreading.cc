/*

	This program has been written in a perfect world

	where there is no such thing as an error.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

static void* threadFunc(void* arg){

	char* s = (char*) arg;

	printf("%s", s);

	//Seems like this kinda acts as an
	//exit status.
	return  (void*) strlen(s);

}

int main(int argc, char *argv[]){
 
	//pthread_t is generally used as an identifier,
	//which is passed in to pthread_create's argument.
	pthread_t t1;

	void *res;

	/*

		For the clarification purpose,
	
		I am passing &t1 because some other

		functions will have to identify that thread.

		And the third argument is the start(),
		
		which is the actual function that

		will start in new thread.
	
		And the last argument, "Hello World\n",
		
		is the argument passed in to the function

		that has been started by a new thread. 				

		
		Previously, it was:
		
		s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");

		and the error was "invalid conversion from const void*

		to void*."

		
		But isn't string already an array?

		Which is already implied that in itself is the
	
		pointer?
		

	*/
	int s;
	s = pthread_create(&t1, NULL, threadFunc, (void*)"Hello world\n");

	//Then the main thread continues...

	//The pthread_join will assign a value from the return status.
	s = pthread_join(t1, &res);			
	
	printf("Thread returned %ld\n", (long)res);

	exit(EXIT_SUCCESS);

	return 0;

}
