/*

	In order for me to test how the child process can return a value,

	I need to make a child process.

	So, the wait() was specifically made to get the state change in the
	
	child process; meaning, by using wait(), I will be able to get the

	resource associated with the child process.

*/
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
/*

	PID is returned, and if 0, the process is determined to be a child.

*/
	int PID = fork();

	int status;	

	if(PID == 0){

		cout << "I am a child process.\n" << endl;

	}else if(PID < 0){
		/*
		
			For some reason, the perror is printing something I've
		
			passed in, and it returns the word success, which
		
			is counter intuitive because shouldn't errors

			produce strings such as, "your program broke?"

		*/
		perror("Why is it telling me that the program was success?-> ");
		cout << "\nExiting the current proces." << endl;
		exit(-1);

	}else{ //Under the assumption that PID is not negative(which signifise that the process is
	       //broken.
	 
		cout << "I am a parent process.\n" << endl;	
		cout << "I am waiting...\n" << endl;		

		//So, wait() has a return value,
		//which will be -1, if the terminated child process is broken.
		if(wait(NULL) == -1){

			perror("The child process is broken.\n");

		}	

		

	}

	return 0;

}
