/*
	
	By the way, in this demo, I am not catching any errors.

*/
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

	using namespace std;

int main(){
/*

	wait() returns the PID of the child.

	According to the man7 page, wait() can actually point to a particular variable,

	and stores the exit status in that variable, of the calling process;

	at least, that's how I am understanding things.

	
	Mr.Jon told me that I have to use the WIFEXITED and WEXITSTATUS

	both at the same time.

*/
	int status = 0;

	int statusValue = 0;

	pid_t exitStatus;

	pid_t PID = fork();

	if(PID == 0){
	
		cout << "I am a child.\n" << endl;
/*

	The exit status must be passed through the exit() function.

*/
		exit(7);		

	}else{

		cout << "I am a parent.\n" << endl;
/*

	Once again, wait() function has a pointer

	paramter, which could point the address of some variable.

*/	
		wait(&status);
/*

	Don't really know the concrete reason why, but the combination of the

	WIFEXITED and the WEXITSTATUS are required in order for the exit status of the

	child process is to be returned.

	(Q: What does the status contain anyways?"
	Anyways, the status can be "passed"(the reason why there are quotation marks
	around the pass is because MACROS are not functions, nothing is really passed)
	to the WIFEEXITED and the WEXITSTATUS, and behave as documented.
	

*/
		if(WIFEXITED(status)){

			cout << "Child exiting the process has been detacted.\n" << endl;

			exitStatus = WEXITSTATUS(status);

		}

		cout << exitStatus << endl;
		
	}

	return 0;

}
/*

	wait passes an address of a variable, and that variable holds the infomation
	of the child process's duration of the run time.

	WIFEXITED "passes" the variable that hold's the child's process, and returns true,
	and WEXITSTATUS also does the same, but actually returns the exit status.

	exit status is returned through the argument of the exit.

	

*/
