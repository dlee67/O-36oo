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

	char buffer[] = "I am writting stuff down.\0";

	int fileDes[2];

	pipe(fileDes);

	int PID = fork();

	if(PID == 0){

		cout << "Child Process is running." << endl;

		close(fileDes[0]);
		
		write(fileDes[1], buffer, sizeof(buffer));

		exit(EXIT_SUCCESS);

	}else{
	
		cout << "Parent process is standing by." << endl;

		wait(NULL);

		close(fileDes[1]);
		/*

			My intuition is telling me that I don't really need a read function if I am going to read everything off from the

			buffer because write function already have written everything down.

			But let's test that out later.

		*/
		//Turns out I was kinda wasting time because buffer is declared outside of
		//each of the child and parent process'es code block; thus,
		//printing out characters from buffer would be done flawlessly.
		//read(fileDes[0], buffer, sizeof(buffer));

		for(int c = 0; c < sizeof(buffer); c++){

			cout << buffer[c];		

		}

		exit(EXIT_SUCCESS);

	}
	
	return 0;

}
