#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

int main(){

	//pid_t ensures that the values can be signed,
	//then again, why not use signed int x;?
	pid_t PID = fork();
	
	//The whole process works bit weird with the status.
	pid_t status;

	int displayStatus;

	if(PID < 0){

		perror("The process has been broke.");
		//What's EXIT_FAILURE again?
		exit(EXIT_FAILURE);

	}else if(PID == 0){

		int check = execl("./Call.o", "7");
		
		if(check == 1){

			perror("That path has not been found.");
			exit(EXIT_FAILURE);

		}

	//Under the assumption that the current process is the parent process.
	}else{

		int checkIfBroke = wait(&status);

		cout << "This is the value of the checkIfBroke: " << checkIfBroke << endl;

		cout << "This is the value of the status: " << status << endl;

		if(checkIfBroke == -1){

			perror("There might be a zombie process");
			exit(EXIT_FAILURE);			

		}else if(WIFEXITED(status)){

			cout << "Termination proceeds normally." << endl;

			//Was previously this, int displayStatus = WEXITSTATUS(status);
			//If it was Java, then the compiler would give me an error and stuff.
			//I am guessing scopes are different for C++.

			//cplusplus.com/doc/tutorial/namespaces/
			//Accroding to the link above, each braces
			//declares a set block of scope.
			/*

				Meaning, for this particular problem,
				int displayStatus = WEXITSTATUS(status); won't trigger an
				error because soon as I created the open and close braces,
				I am telling the compiler that, "this displayStatus variable
				does not use the memory space of the displayStatus outside of the
				scope." Therefore, soon as I get rid of the int data declaration
				right next to the displayStatus, everything will work as intended
				because now I am telling the compiler that, "this displayStatus
				variable IS the displayStatus varaible outside of this scope."

			*/			

			displayStatus = WEXITSTATUS(status);
		
			cout << "The displayStatus in the else if block: " << displayStatus << endl;

		}

	}

	cout << "Exit status of the Call.o: " << displayStatus << endl;

	return 0;

} 
