/*

	I am assuming the program over here represents the producer.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unist.h>
#define MAXSIZE 100

int main(int argc, char** argv){
	
	//Shared memory ID.
	int shmid;
	
	//Key
	key_t key;

	//Shared memory
	//Was previously int *shm;
	void *shm;

	char *s;

	key = 9876;

	//shmget is the function that provides a shared memory for me.
	shmid = shmget(key, MAXSIZE, IPC_CREAT | 0777);

	if(shmid < 0){

		perror("shmget");
		exit(1);

	}
	
	//I know why the compiler is screaming at me.
	//So, shmat returns a void pointer, while shm previous was int *shm; 
	shm = shmat(shmid, NULL, 0);

	if(shm == (char*) - 1){

		perror("shmat");
		exit(1);

	}

	memcpy(shm, "Hello World", 11);

	s = shm;

	s += 11;

	//In all obviousness, the zero represents a null terminator
	*s = 0;

	while(*shm != '*'){

		sleep(1);

	}

	return 1;

}
