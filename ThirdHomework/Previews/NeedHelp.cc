/*

	Obviously, the reading end is not cutting off nicely,

	My speculation as of now is that read() is reading too much,

	or write() is writing too much.	

	06/18/17

	Somewhere around 4:50PM

	if things get fixed, I should concern about: write(STDOUT_FILENO, buffer, strlen(streamThis));

	Why wasn't the function above worked?


	06/18/17

	05:11PM

	I have a firm belief that I am wrinting things out with STDOUT_FILENO correctly.

	

	05:44PM

	strlen(streamThis) broke everything.

	05:50PM

	Comparing this source to AfterAWhile, AfterAWhile has sizeof() for the third argument,

	that will certainly break the AfterAWhile.cc because


*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main(){

	char streamThis[] = "Hi, I am so cool.\n";

	char buffer[strlen(streamThis)];

	int fileDes[2]; 
	pipe(fileDes);

	int PID = fork();

	if(PID == 0){

		close(fileDes[1]);

		//int breakOut = read(fileDes[0], buffer, strlen(streamThis));
		read(fileDes[0], buffer, sizeof(buffer));

		write(STDOUT_FILENO, buffer, sizeof(buffer));

		exit(EXIT_SUCCESS);

	}else{

		close(fileDes[0]);

		//The third argument was strlen(streamThis) before.
		write(fileDes[1], streamThis, strlen(streamThis));

		wait(NULL);

	}

}
