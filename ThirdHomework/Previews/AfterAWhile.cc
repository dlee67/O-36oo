/*

	Have a stream of string be printed out through the child process,

	without using argv from main function's argument.

	

	read() won't return 0, unless it reaches the indication of the end of the file.

*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main(){

	char streamThis[] = "Hi, I am so cool.\0";

	char buffer[20];

	int fileDes[2]; 

	cout << sizeof(buffer) << endl;

	//Need to create one because
	//pipe is a method of communication,
	//but not a bridge of anysort.
	pipe(fileDes);

	int PID = fork();

	if(PID == 0){

	//while(1){

		close(fileDes[1]);

		//I am putting sizeof(buffer) for now because
		//I don't know how to catch an end of the file yet.
		int breakOut = read(fileDes[0], buffer, sizeof(buffer));
	
		//if(breakOut == '0'){
		//	break;		
		//}		
		
		//By passing in STDOUT_FILENO, I am communicating with the file descriptor table,
		//telling it to print out things from the 2nd argument.
		
		//Then again, read() and write() both have 3rd argument that will read up to specified amount,
		//my intuition is telling me that I don't really need loop,
		//I am guessing it's for the synchronization between parent sending things and child receiving things.
		write(STDOUT_FILENO, buffer, sizeof(buffer));

		//write(STDOUT_FILENO, "\n", 1);	
		
		//The program is not breaking out of the loop.
	
	//}	

		exit(EXIT_SUCCESS);

	//Parent should send something to child.
	}else{

	//Still am not sure of critical reason of why to close fileDes[0].
	close(fileDes[0]);

	//Throught the pipe, which is the write end of the pipe(which is indicated by fileDes[1]), 
	//the parent will send a stream of inputs to the read end of the pipe.
	write(fileDes[1], streamThis, strlen(streamThis));

	wait(NULL);

	}

}

