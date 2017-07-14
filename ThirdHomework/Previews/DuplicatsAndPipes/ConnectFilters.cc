/*

	The objective is to connect filters, anything is fine really.

	echo Hello World | wc -l   // <- Maybe that's a good exercise?


	child echo Hello World

	
	I did it.

*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>

int main(){

	int pfd[2];

	pipe(pfd);

	int child1 = fork();

	if(child1 == -1){

		perror("fork");
		exit(EXIT_FAILURE);

	}else if(child1 == 0){

		close(pfd[0]);

		dup2(pfd[1], STDOUT_FILENO);

		close(pfd[1]);
		
		execlp("echo", "echo", "Hello World", (char*)NULL);
	}

	int child2 = fork();

	if(child2 == -1){

		perror("fork");
		exit(EXIT_FAILURE);

	}else if(child2 == 0){

		close(pfd[1]);
		
		//Which I am assuming that kernel only looks for the index number when looking thorugh the
		//fd table.
		dup2(pfd[0], STDIN_FILENO);
		
		//Thus, getting rid of pfd[0] doesn't make any differences, for there is already pfd[0] in the
		//index number 0 of fd table.
		close(pfd[0]);

		execlp("wc", "wc", "-l", (char*)NULL);	

	}

	close(pfd[0]);
	close(pfd[1]);

	//The reason why we need two wait function is because the parent process comes out of the suspend when
	//any child process terminates.
	wait(NULL);
	wait(NULL);

	return 0;

}
