#include <pthread.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

//The forth argument.
static void* threadFunc(void *arg){

	//Type cast whatever that has been passed through void *arg,
	//and dereference it so that we have the value out of it.
	int loops = *((int*)arg);

	int loc, j, s;

	for(j = 0; j < loops; j++){

		/*

			You know how threads are started by passing in the functions and stuff?

			When a thread begins to execute the function, seems like mutex doesn't allow any

			timeshare to other threads, just my opinion.

		*/

		s = pthread_mutex_lock(&mtx);

		if(s != 0){

			perror("mutex");
			exit(EXIT_FAILURE);

		}

		loc = glob;
		
		loc++;

		glob = loc;

		
		s = pthread_mutex_unlock(&mtx);

		if(s != 0){
		
			perror("mutex");
			exit(EXIT_FAILURE);

		}
	}

	return NULL;

}

int main(int argc, char** argv){

	pthread_t t1, t2;

	int loops, s;
/*

	I really should use a function that changes a char value to int value regardless of the size, 

	the tecnique I am using below only applies to 0 to 10 number.
	
	//Doing something like that makes everything more complicated, in fact, I don't know how to convert things at this point.
	//char* conv = argv[1];

	//A correct approach is more like the line below because we already know that argv is a pointer to a pointer, 
	//which is abled to be dereferenced.
	char conv = *argv[1];

	//The line below looks very chaotic.	
	//loops = (int*)conv - (int*)'0';

	//Now everything converts very nicely.
	loops = (int)conv - (int)'0';
*/
	
	loops = atoi(argv[1]);

	cout << loops << endl;		

	//The forth argument cannot be literals because forth parameter is a pointer,
	//where I will have to pass in an address.
	s = pthread_create(&t1, NULL, threadFunc, &loops);
	s = pthread_create(&t2, NULL, threadFunc, &loops);

	//The second argument is null because a variable we are playing around is global already.
	s = pthread_join(t1, NULL);

	//The second argument is null because the same reason as above.
	s = pthread_join(t2, NULL);

	cout << "glob = " << glob << endl;

	exit(EXIT_SUCCESS);

}


