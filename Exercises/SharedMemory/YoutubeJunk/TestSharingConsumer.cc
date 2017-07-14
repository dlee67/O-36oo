/*

	I am assuming the program over here represents the producer.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAXSIZE 100

int main(int argc, char *argv[]){
	
	//Shared memory ID.
	int shmid;
	
	//Key
	key_t key;

	//Shared memory
	char *shm;

	char *s;

	key = 9876;
	
	//From the consumer's side, IPC_CREATE is not required because
	//memory space is not being allocated.
	shmid = shmget(key, MAXSIZE, 0777);

	if(shmid < 0){

		perror("shmget");
		exit(1);

	}
	
	shm = shmat(shmid, NULL, 0);

	if(shm == (char*) - 1){

		perror("shmat");
		exit(1);

	}

	memcpy(shm, "Hello World", 11);

	for(s = shm; *s != 0; s++){

		cout << "\n" << *s << endl;
		
	}

	cout << "\n" << endl;

	*shm = '*';

	return 1;

}
