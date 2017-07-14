#include <pthread.h>
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

void* threadFunction(void* arg){

	cout << (char*)arg << endl;

	cout << "Lulz!!!" << endl;

	return (void*)"Somewhere in the memory";

}

int main(){

	pthread_t t1;

	//It's like the exit status that I had to catch
	//in the first homework assignment.
	//This time, the place of retval is the pointer...
	void* ret;

	int errCheck = pthread_create(&t1, NULL, threadFunction, (void*)"Pass"); 	

	pthread_join(t1, &ret);
	
	/*

		Previously, it was:

		cout << *ret << endl;

		Seems like cout doesn't know how to print out
		
		void pointers, so I have to type cast it
	
		so that it prints out characters.

	*/
	cout << (char*)ret << endl;

	return 0;

}
