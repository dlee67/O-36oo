//When compiling a source file with pthread, I have to compile it with -pthread option.
//When things aren't working, do something different.
/*

	There is also something called pthread_detach, which reclaims the memory

	where the thread was running in.

	Thus, freeing and claiming memories with threads are near essential.

*/
/*

	To wait for a particular thread to finish, one way of doing it is to use pthread_join

*/
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//Writing down a static keyword means a particular variable will be visible
//to all other memories.
static int glob = 0;

//In order to use a mutex, I have to innitialize it.
//There is a whole story about POSIX library also allows
//the innitialization of pthread to happen, but
//doesn't always has to be the case.
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/*

	Spent about good 30 minutes trying to figure out why this source wasn't compiling.

	static void threadFunction(){} <- That was the previous the way the function header was written.

	In the man page, the third function argument is void *(*start_routine)(void*).

	So, whatever I have to pass into a function that the thread will play around must return void pointer,
	
	and whatever I pass into the function able to be pointed by a void pointer.

*/
static void* threadFunction(void *arg){
	
	//So, a pointer type can only be type casted to other pointer type.
	/*

		04:43PM

		char someString = *((char*)arg);

		When I pass in NULL into this function with the above function,

		then the program tells me that there is a segfault, and doesnt run.	
	
	*/
	

	cout << "Hello World" << endl;

	//cout << "Hello World" << endl;			

	return NULL;

}

int main(int argc, char** argv){

	//pthread_t is written down because .h file are usually composed with structs.
	//t1 and t2 represents the threads.	
	pthread_t t1, t2;

	//char* iAmString = "Hello World";
	
	pthread_create(&t1, NULL, threadFunction, NULL);	

	//According to the StackOverFlow, main thread could exit before other "sub-threads" can do anything.

	void *basket;

	int isItBroken = pthread_join(t1, NULL);

	return 0;

}
