/*

	Seems like semaphor is one of software entity that is shared by the 

	related processes.

	However, it is probably a good idea to cofirm my understandings regarding the

	mutex and semaphor, and actually understand how the semaphor is shared.

*/
#include <signal.h>
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

static int semid = semget(IPC_PRIVATE, 1, 0777);

static sembuf sop;

void sigHandler(int sigNum){

	cout << "signal has been sent." << endl;

	sop.sem_op = 1;

	semop(semid, &sop, 1);

}

int main(){

	sop.sem_op = 0;
	sop.sem_flg = 0;
	sop.sem_num = 0;

	int errorCheck;
	
	cout << "The program is now starting." << endl;

	struct sigaction action;
	
	struct sigaction action2;

	struct sigaction action3;

	action.sa_handler = sigHandler;
	
	action2.sa_handler = sigHandler;

	action3.sa_handler = sigHandler;

	errorCheck = sigemptyset(&action.sa_mask);	

	if(errorCheck != 0){

		perror("sigemptyset");
		exit(EXIT_FAILURE);

	}

	int checkErr = sigaction(SIGUSR1, &action, NULL);

	int checkErr2 = sigaction(SIGUSR2, &action2, NULL);

	int checkErr3 = sigaction(SIGHUP, &action3, NULL);

	if(checkErr || checkErr2 || checkErr3){

		perror("sigaction");
		exit(EXIT_FAILURE);

	}

	pid_t PID = fork();

	if(PID == -1){

		perror("fork");
		exit(EXIT_FAILURE);

	}	

	if(PID == 0){
		
		sop.sem_op = -1;

		kill(getppid(), SIGUSR1);

		semop(semid, &sop, 1);

		sleep(1);

		kill(getppid(), SIGUSR2);
			
		semop(semid, &sop, 1);

		sleep(1);

		kill(getppid(), SIGHUP); 

		semop(semid, &sop, 1);

		sleep(1);

		kill(getppid(), SIGUSR1);	

		semop(semid, &sop, 1);

		sleep(1);

		kill(getppid(), SIGUSR1);
		
		semop(semid, &sop, 1);
	
		sleep(1);
	
		kill(getppid(), SIGUSR1);

		semop(semid, &sop, 1);

		sleep(1);

		exit(EXIT_SUCCESS);

	}else{

		pause();

		pause();

		pause();

		pause();
	
		pause();

		wait(NULL);

		sleep(1);

		cout << "\nParent process is now finishing." << endl;

	}
}
