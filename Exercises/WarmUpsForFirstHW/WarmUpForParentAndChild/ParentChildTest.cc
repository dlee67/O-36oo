#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(){

	int PID = fork();

	int status;

	int returnStatus;

	if(PID == 0){

		cout << "Exiting with the value 7." << endl;
		
		exit(7);

	}else{
		
		wait(&status);			
			
		if(WIFEXITED(status)){

			returnStatus = WEXITSTATUS(status);

		}

	}

	cout << "Child's return status is: " << returnStatus << endl;

	if(returnStatus == 7){

		cout << "The program was successfully executed." << endl;	

	}

	return 0;

}
