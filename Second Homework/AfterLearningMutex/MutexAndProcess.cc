#include <signal.h>
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

/*

	After making some adjustments, I've decided to have 3 additional signals be sent to the parent process.

	Things are still breaking, but system reboots after 2 or 3 seconds have passed.

*/

using namespace std;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void sigHandler(int sigNum){

	pthread_mutex_lock(&mutex);

	cout << "signal has been sent." << endl;

	pthread_mutex_unlock(&mutex);

}

int main(){

	cout << "The program is now starting." << endl;

	struct sigaction action;
	
	struct sigaction action2;

	struct sigaction action3;

	action.sa_handler = sigHandler;
	
	action2.sa_handler = sigHandler;

	action3.sa_handler = sigHandler;

	sigemptyset(&action.sa_mask);	

	int checkErr = sigaction(SIGUSR1, &action, NULL);

	int checkErr2 = sigaction(SIGUSR2, &action2, NULL);

	int checkErr3 = sigaction(SIGHUP, &action3, NULL);

	pid_t PID = fork();

	if(PID == -1){

		perror("fork");
		exit(EXIT_FAILURE);

	}	

	if(PID == 0){
		
		//pthread_mutex_lock(&mutex);

		kill(getppid(), SIGUSR1);

		sleep(1);

		//pthread_mutex_unlock(&mutex);

		//pthread_mutex_lock(&mutex);

		kill(getppid(), SIGUSR2);
			
		sleep(1);

		//pthread_mutex_unlock(&mutex);

		//pthread_mutex_lock(&mutex);

		kill(getppid(), SIGHUP); 

		sleep(1);

		//pthread_mutex_unlock(&mutex);

		//pthread_mutex_lock(&mutex);

		kill(getppid(), SIGUSR1);	
		
		sleep(1);

		//pthread_mutex_unlock(&mutex);

		//pthread_mutex_lock(&mutex);

		kill(getppid(), SIGUSR1);

		sleep(1);

		//pthread_mutex_unlock(&mutex);

		//pthread_mutex_lock(&mutex);
	
		kill(getppid(), SIGUSR1);

		//sleep(1);

		//pthread_mutex_unlock(&mutex);
		
		exit(EXIT_SUCCESS);

	}else{

		if(checkErr == -1){

			perror("sigaction");
			exit(EXIT_FAILURE);

		}

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
