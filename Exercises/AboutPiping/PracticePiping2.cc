/*

	Everything was written under the assumption that nothing will break.

*/
#include <unistd.h> //For fork() and pipe()
#include <stdlib.h> //For exit()
#include <iostream>
#include <stdio.h> //For perror()
#include <sys/wait.h>
#include <string.h>

#define BUF_SIZE 10

using namespace std;

int main(int argc, char** argv){

	ssize_t	numRead;
	
	char buffer[BUF_SIZE];
	//Still unclear why I would need 2 indices.
	int pipeFeed[2];

	pipe(pipeFeed);

	pid_t PID = fork();

	//I want the child process to write things out into the output.
	if(PID == 0){
		
		//This needs to be done so that Kernel knows that nothing is being written
		//to the file descriptor.
		close(pipeFeed[1]);

		//numRead, the variable, does not contribute to the piping,
		//it's more for error checking.
		numRead = read(pipeFeed[0], buffer, sizeof(buffer));

		write(STDOUT_FILENO, buffer, sizeof(buffer));

		write(STDOUT_FILENO, "\n", 1);

	//The parent
	}else{
		//Must close pipeFeed[0], since no reading is being done.
		close(pipeFeed[0]);

		write(pipeFeed[1], argv[1], sizeof(argv[1]));
		
		//Until the child process finishes every operation,
		wait(NULL);

		exit(EXIT_SUCCESS);

	}

	return 0;

}
