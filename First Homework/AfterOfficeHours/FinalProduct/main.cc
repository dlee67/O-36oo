#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){

	int childPID = fork();

	int status;

	int displayedStatus;
	if(childPID == -1){

		perror("fork");

		exit(EXIT_FAILURE);

	}else if(childPID == 0){

		int notFound = execl("./counter.o", "5", (char*)NULL);

		if(notFound == -1){

			perror("execl");

			exit(EXIT_FAILURE);

		}

	}else{

		int isItZombie = wait(&status);

		if(WIFEXITED(status)){

			displayedStatus = WEXITSTATUS(status);

		}else if(isItZombie == -1){


			perror("wait");

			exit(EXIT_FAILURE);
			

		}

	}

	cout << "Process " << childPID << " exited with status: " << displayedStatus << endl;

	return 0;

}
