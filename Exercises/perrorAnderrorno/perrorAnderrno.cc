#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

using namespace std;

int main(){

	int PID = -1;

	if(PID == 0){

		cout << "I am a child." << endl;

		cout << "This child has, for parents: " << getppid() << endl;

	}else if(PID < 0){

		perror("It says success->: ");

	}else{

		wait(NULL);
	
		cout << "I am a parent process." << endl;
	
		cout << "Parent's getppid(): " << getppid() << endl;		

		//The below will return the child PID.
		//cout << "Appearantly the PID of the child: " << PID << endl;

	}

	return 0;

}
