/*
	
	First of all, I need to have in consideration that semaphores are possible to be interacted with

	with struct sembuf types because sembufs gets passed into the semop().

	
	semop() stands for semaphor operation, not semaphor open.




	Then there is union semun type, where it is passed into the semctl() function.

	
	semctl() function is, in my opinion, same philosophy as the semop(), but more intecracy behind it.

	
	
	semget() is the function that innitializes the semphor set in the system v IPC API.	

*/
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

union semun{

	int val;

	struct semid_ds* buf;
	
	unsigned short* array;
		
	struct seminfo* __buf;

};

int main(int argc, char *argv[]){

	int semid;

	if(argc == 2){

		union semun arg;

		semid = semget(IPC_PRIVATE, 1, 0777);
	
		arg.val = atoi(argv[1]);

		semctl(semid, /*semnum = */ 0, SETVAL, arg);

		printf("Semaphor ID = %d\n", semid);

	}else{

		struct sembuf sop;

		semid = atoi(argv[1]);

		sop.sem_num = 0;

		sop.sem_op = atoi(argv[2]);

		sop.sem_flg = 0;

		printf("%ld: about to semop.\n", (long)getpid());	

		printf("%ld: semop completed", (long)getpid());

	}
	
	exit(EXIT_SUCCESS);

	return 0;

}

