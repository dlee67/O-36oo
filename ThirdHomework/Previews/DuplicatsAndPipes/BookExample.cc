/*
	
	After replacing execl with execlp,

	things started to work.

	The differences between the execl and execlp is that

	the execl will need a specification for the file path.

	The execlp will need a specification for the file.

	Meaing, using execl, for this context, will require for me to

	get the path for ls and wc, whicl execlp only need the name of the file.

*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>
#include <sys/wait.h>

int main(){

	int pfd[2];

	pipe(pfd);

	//First child exec ls to write to pipe
	switch(fork()){

		case 0:
			//Yes, the read end is unused.
			close(pfd[0]);

			dup2(pfd[1], STDOUT_FILENO);
		
			close(pfd[1]);	
			//Since, whatever that is written to input needs to go through STDOUT_FILENO, in this particular case, 
			//the output is sent through the pipe.
			//The explanation could be that whenever kernel is analyzing the incoming input from the particular 
			//process, it looks at the index 1 in the file descriptor table.
			execlp("ls", "ls", (char*)NULL);
		
		default:

			break;

	}		

	switch(fork()){
	
		case 0:

			close(pfd[1]);
			
			dup2(pfd[0], STDIN_FILENO);
			
			close(pfd[0]);

			execlp("wc", "wc", "-l", (char*)NULL);

		default:

			break;	
	
	}



	close(pfd[0]);

	close(pfd[1]);
	
	//Why two wait?
	wait(NULL);
	wait(NULL);

	exit(EXIT_SUCCESS);

}
