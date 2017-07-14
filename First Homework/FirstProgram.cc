#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char** argv){

	char pound = *argv[0];
	
	int exitStatus = pound - '0';

	int childPID = getpid();

	int parentPID = getppid();

	cout << "Child PID: " << childPID << endl;

	cout << "Parent PID: " << parentPID << endl;

	for(int x = 0; x < exitStatus; x++){

		cout << "Process: " << childPID << " " << x + 1 << endl;

	}

	exit(exitStatus);
	
	return 0;

}
