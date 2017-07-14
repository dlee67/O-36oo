/*
	
	Thread-local variables are a lot easier than the thread-specific data.

	Despite the fact that name says thread-local variable, we have to make a global or static variable.

	
	
	By the way, segmentation fault means I've tried to access a memory that I don't have the permission to.

*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>                                                                                                                                     
#include <iostream>

#define MAX_ERROR_LEN 256

using namespace std;

//the below commented out code are examples from book.
//static _thread char buf[MAX_ERROR_LEN];
/*
char* strerror(int err){

	if(err < 0 || err >= _sys_nerr || _sys_errlist[err] == NULL){
		snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", err); 	
	}else{
		strncpy(buf, _sys_errlist[err], MAX_ERROR_LEN - 1);
		buf[MAX_ERROR_LEN - 1] = '\0'
	}

	return buf;

}
*/

//The mechanism is that if a particular data is statically defined, then
//any software entities in the memory section, which is part of the memory
//section the thread-local variable is, then all the threads are
//naturally able to share it.

//Also, p.s, the book has a ambigious way of putting underscores twice.

static __thread int data;

void* doSomething(void* arg){

	data = 777;

	cout << &data << endl;

	return (void*)data;
	
}

int main(){

	pthread_t t1;
	
	void* getData;

	//Well, makes sense, because if thread were to run, I have to identify it,
	//and there must be a software entity that runs the thread.
	pthread_create(&t1, NULL, doSomething, NULL);

	pthread_join(t1, &getData);

	cout << &data << endl;

	//Look, pointer pointer.
	//int* convData = (int*)getData;
	//Even after doing writing something like
	//code below, I am still getting segmentation fault, 
	//I am guessing that's happenning because
	//static defined variables cannot be dereferenced, or something.
	//int convData = *((int*)getData);

	cout << data << endl;

	return 0;

}
