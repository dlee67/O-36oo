#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>

using namespace std;

union semun{

	int val;

	struct semid_ds* buf;

	unsigned short* array;

	struct seminfo* __buf;

};

int main(){

	union semun arg;

	int semid = semget(IPC_PRIVATE, 1, 0777);

	arg.val = 0;

	semctl(semid, 0, SETVAL, arg);	

	//Look, I did it.
	cout << semctl(semid, 0, GETVAL) << endl; 

	//Decreasing semval throught semun does not decrease the semval's value below 0.
	//arg.val = -3;
	arg.val = 1;

	semctl(semid, 0, SETVAL, arg);

	//The values of the semctl changes according to the arg.
	cout << semctl(semid, 0, GETVAL) << endl;

	//As of now, it seems like the interactions between the semctl and the semaphor object is done through semun
	//because it is directly stated that the semun's val member's value assigned to the semaphor object's 
	//semval associated value.

	//However, using semctl doesn't go along with the term operation, the book says initialize or control operation.

	struct sembuf sop;

	sop.sem_num = 0;

	//Having semval be negative thorught sem_op LOCKS the entire flow of the process.
	//sop.sem_op = -2;
	sop.sem_op = 1;
	
	sop.sem_flg = 0;


	//...? What's the point of using semctl(semid, 0, SETVAL, arg); when semop(semid, &sop, 1) is simpler by times 10.
	semop(semid, &sop, 1);

	cout << semctl(semid, 0, GETVAL) << endl;

	return 0;

}
