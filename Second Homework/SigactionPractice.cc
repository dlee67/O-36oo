#include <signal.h>
#include <iostream> //Despite what people say, I think manuel testing is great!
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void sigHandler(int sigNum){
	/*
	
		Needs to be pointed by the sigactions.

	*/
	
	cout << "\nInterrupt has been caught." << endl;

}

int main(int argc, char** argv){
	
	//Unless I am using new/delte procedure, I don't need a pointer for the action.
	//Anyway, I am innitializing the sigaction.	
	struct sigaction action;

	//Don't really know how to express this, but I will try my best.
	/*

		So, sigaction is a struct that holds members those are related to the
		
		signaling of many things, and one of the member is something called 

		*sa_handler, which holds the pointer to a particular signal handling function.

	
	*/
	action.sa_handler = sigHandler;

	//If I don't put in ampersend, then the thing will scream at me.
	sigemptyset(&action.sa_mask);

	action.sa_flags = 0;
	
	//The compiler screams at me if I don't put ampersend right next to action.
	int errCheck = sigaction(SIGINT, &action, 0);

	if(errCheck == -1){

		perror("sigaction");
		exit(EXIT_FAILURE);

	}

	while(1){

		cout << "\nWell, at least the child can now grap the sig action." << endl;

		sleep(1);
	
	}
/*	
	pid_t PID = fork();

	if(PID < 0){

		perror("fork");
		exit(EXIT_FAILURE);

	}	

	if(PID == 0){
	
		

	}

	return 0;
*/
}
