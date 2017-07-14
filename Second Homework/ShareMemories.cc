#include <signal.h>
#include <iostream> //Despite what people say, I think manuel testing is great!
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define buffsize 100

char maxSize[buffsize];

using namespace std;

void sigHandler(int sigNum){
	
	cout << "signal has been sent." << endl;

}

int main(){

	cout << "The program is now starting." << endl;

	struct sigaction action;
	
	action.sa_handler = sigHandler;
	
	sigemptyset(&action.sa_mask);	

	int checkErr = sigaction(SIGUSR1, &action, NULL);

	pid_t PID = fork();

	if(PID == -1){

		perror("fork");
		exit(EXIT_FAILURE);

	}	

	if(PID == 0){
		
		kill(getppid(), SIGUSR1);	
		/*

			06/12/17

			07:00PM

			I am not sure if I am using the right statements to describe what I'am doing wrong, or right,

			but seems like signalings must be "synchronized on their own."

			Meaning, sending of signals are bound to be out of order, if not maintained to be synchronized because

			of the precedencies that takes internally.

			This, calling sleep system calls on the child process has the process wait until the signal has been called properly, then
	
			moves on to call the next signal.

		*/
		sleep(1);

		kill(getppid(), SIGUSR1);

		sleep(1);

		kill(getppid(), SIGUSR1);

		exit(EXIT_SUCCESS);

	}else{

		if(checkErr == -1){

			perror("sigaction");
			exit(EXIT_FAILURE);

		}

		/*

			06/12/17

			07:00PM

			pause system calls are placed because it enables the parent process to be in suspend until the signal is sent from child.

			It might be intuitively make sense to think that wait function will deal with that naturally, but it wasn't the case.

		*/

		pause();

		pause();
		
		wait(NULL);

		sleep(1);

		cout << "\nParent process is now finishing." << endl;

	}
}
