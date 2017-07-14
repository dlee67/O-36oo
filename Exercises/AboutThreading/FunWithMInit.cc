/*

	So, mutex is like sort of,..
	ur...
	hm

	An object that mitigates which threads run or dont?

	Long as they are innitialized somehow, they work
	
	healthy and dandy.

*/
#include <pthread.h>
#include <stdlib.h>
#include <iostream>

static int basket = 0;

static int basket2 = 0;

//static pthread_mutex_t theMutex;

using namespace std;

static void* threadFunction(void* arg){

	int loc, c;
	
	for(c = 0; c < 10; c++){

		//pthread_mutex_lock(&theMutex);
		
		loc = basket;

		//loc = basket2;

		loc++;		
		
		basket = loc;

		//basket2 = loc;		

		//pthread_mutex_unlock(&theMutex);

	}

}

int main(){

	pthread_t t1, t2;

	//The below lines of codes are useless, at least under the context of C++
	//because theMutex object needs to be visible in the start functions.
	//pthread_mutex_t theMutex;

	int* return1 = &basket; 
	
	int* return2 = &basket2;
	
//	pthread_mutex_init(&theMutex, NULL);	

	pthread_create(&t1, NULL, threadFunction, NULL);

	pthread_create(&t2, NULL, threadFunction, NULL);

	pthread_join(t1, NULL);

	pthread_join(t2, NULL);

	
	//Previously has those, with int* return1, return2; somewhere in the source.
	//return1 = &basket;	
	//return2 = &basket2;

	cout << "Basket has a value of: " << *return1 << endl;

	cout << "Basket2 has a value of: " << *return2 << endl;

	return 0;

}
