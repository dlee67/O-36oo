/*

	Let's try to tackle the create and join.

	Now, let's try to use a retrieval with pthread_join.

*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* coolThread(void){ //void* arg){

	
	sleep(1);
	

	void* x;

	printf("Super cool thread only for 39.99\n");

	return x;

}

int main(int argc, char** argv){

	printf("Program starting because it's cool\n");

	pthread_t t1;

	void* x;

	int checkErr = pthread_create(&t1, NULL, coolThread, argv[1]);	
	
	if(checkErr != 0){

		perror("pthread_create");
		exit(EXIT_FAILURE);

	}	

	int checkErr2 = pthread_join(t1, x);

	if(checkErr != 0){

		perror("pthread_join");
		exit(EXIT_FAILURE);

	}

	int convVoid = *((int*)x);

	printf("My number: %d", convVoid); 
	
	return 0;

}
