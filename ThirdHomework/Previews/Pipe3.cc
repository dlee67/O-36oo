/*

	The objective is to learn more about piping by having the child processor 

	write something to buffer, and parent process read those things from the buffer.

	W/o error checkings.

*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>

using namespace std;

int main(){

	//If I were to write anything, then I need to 
	char buffer[]; //= "I am writting stuff down.\0";

	int fileDes[2];

	pipe(fileDes);

	int PID = fork();

	if(PID == 0){

		cout << "Child Process is running." << endl;

		close(fileDes[0]);
		
		write(fileDes[1], buffer, sizeof(buffer));

		exit(EXIT_SUCCESS);

	}else{
	/*
		cout << "Parent process is standing by." << endl;

		wait(NULL);

		close(fileDes[1]);
		
		exit(EXIT_SUCCESS);
	*/

		wait(NULL);

		cout << "Parent Process is running." << endl;

		close(fileDes[0]);
		
		write(fileDes[1], buffer, sizeof(buffer));

		exit(EXIT_SUCCESS);

	}
	
	return 0;

}
