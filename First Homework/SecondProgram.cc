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

	if(childPID == 0){

		execl("./FirstProgram.o", "5");

	}else{

		wait(&status);

		if(WIFEXITED(status)){

			displayedStatus = WEXITSTATUS(status);

		}

	}

	cout << "Process " << childPID << " exited with status: " << displayedStatus << endl;

	return 0;

}
