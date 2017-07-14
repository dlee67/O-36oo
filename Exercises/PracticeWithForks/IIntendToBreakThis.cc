/*

	If I don't have the max number of processes limited to 1,

	then the fork() won't return 0.

*/
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

using namespace std;

int main(){

	pid_t PID = fork();
	
	if(PID == -1){

		perror("fork() broke");
		exit(EXIT_FAILURE);
		
	}

	cout << "It didn't break" << endl;

	return 0;

}
