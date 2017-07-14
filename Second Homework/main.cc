#include <signal.h>
#include <iostream> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*

	06/18/17

	I came back to apply a final touch; ironically,
		
	when applying fail safes such as perror and if block,
		
	the entire system restarts.

	At this point, I don't really know how to solve problems such as this,
	
	and the worst part about this is that I don't know what could possibly cause

	error such as this.

*/

using namespace std;

void sigHandler(int sigNum){

	cout << "signal has been sent." << endl;

}

int main(){

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
		
		errorCheck = kill(getppid(), SIGUSR1);

		if(errorCheck != 0){

			perror("kill");
			exit(EXIT_FAILURE);
	
		}

		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		errorCheck = kill(getppid(), SIGUSR2);
			
		if(errorCheck != 0){
		
			perror("kill");
			exit(EXIT_FAILURE);	

		}

		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		errorCheck = kill(getppid(), SIGHUP); 

		if(errorCheck != 0){

			perror("kill");
			exit(EXIT_FAILURE);

		}

		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		errorCheck = kill(getppid(), SIGUSR1);	

		if(errorCheck != 0){

			perror("kill");
			exit(EXIT_FAILURE);

		}
		
		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		errorCheck = kill(getppid(), SIGUSR1);

		if(errorCheck != 0){

			perror("kill");
			exit(EXIT_FAILURE);

		}

		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);		

		}

		errorCheck = kill(getppid(), SIGUSR1);

		if(errorCheck != 0){

			perror("kill");
			exit(EXIT_FAILURE);

		}

		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		exit(EXIT_SUCCESS);

	}else{


		errorCheck = pause();

		if(errorCheck != 0){

			perror("pause");
			exit(EXIT_FAILURE);

		}

		errorCheck = pause();

		if(errorCheck != 0){

			perror("pause");
			exit(EXIT_FAILURE);

		}

		errorCheck = pause();

		if(errorCheck != 0){

			perror("pause");
			exit(EXIT_FAILURE);

		}

		errorCheck = pause();

		if(checkErr != 0){

			perror("pause");
			exit(EXIT_FAILURE);

		}

		errorCheck = pause();

		if(errorCheck != 0){

			perror("pause");
			exit(EXIT_FAILURE);

		}

		/*

		pause();

		pause();

		pause();

		pause();
		
		*/

		errorCheck = wait(NULL);

		if(errorCheck != 0){
	
			perror("wait");
			exit(EXIT_FAILURE);

		}
		
		errorCheck = sleep(1);

		if(errorCheck != 0){

			perror("sleep");
			exit(EXIT_FAILURE);

		}

		cout << "\nParent process is now finishing." << endl;

	}
}
