/*

	Be aware of the fact that shared memory is different from the dynamic memory.

*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define MAXSIZE 100

using namespace std;

int main(int argc, char** argv){

	//Shared memory ID.
	int shmID;
	
	//Key
	key_t key;

	//Shared memory
	//Was previously int *shm;
	void *shm;	
	
	key = 9876;

	//shmid ultimately makes a section of shared memory for me,
	//at the sametime, shmget will also return the shared memory 
	//identifier.
	shmID = shmget(key, MAXSIZE, IPC_CREAT | 0777);
	
	if(shmID == -1){

		perror("shmid");
		exit(1);

	}
	
	//Meaning, I am giving the reference to of the memory I've just created
	//to a particular pointer.
	//Since, the shmid now hold the identifier for the shared memory,
	//it needs to be used along with shmat to give a legitament pointer to
	//some identifier.
	//When I pass in NULL for the second parameter, the function will find an arbitrary address
	//for me to start the shared memory.
	//And... other demonstrations for this partucular functions have 0 for the third arguments...
	//don't really know what that does.	
	shm = shmat(shmID, NULL, 0);
	
	/*
	The body of code below will cause a compilation error because 
	void* is not pointer to an object type.
	Ultimately, shm cannot be compared to the -1, but shmat return -1 when 
	error was caused,
	what should I do?
	if(shm == -1){

		perror("shm");
		exit(1);

	}
	*/
	//Seems like the address below is the start of the shared memory.
	cout << &shm << endl;

	return 0;

}
