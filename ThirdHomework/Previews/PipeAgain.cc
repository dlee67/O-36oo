#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>

/*

	My intuition is telling me buffer is like a place to writing something in down,

	and I can grab it whenever I want.

	

	To be more specific about my understanding with buffer, it a allocated memory ready to be transferred
	
	around to other memory.

*/

using namespace std;

int main(){

	char buffer[] = "Look, I am writting something.";

	int fileDes[2];

	int errorCheck;

	errorCheck = pipe(fileDes);

	if(errorCheck != 0){

		perror("pipe");
		exit(EXIT_FAILURE);

	}

	int PID = fork();

	//if(PID != 0){

	//	perror("fork");
	//	exit(EXIT_FAILURE);

	//}

	//Now at child process.
	//Let's make it write something.
	if(PID == 0){

		cout << "Child is running." << endl;

		close(fileDes[0]);

		//When passing in buffer, I am giving them an address.
		//When passing in buffer[0], I am giving them a char value.
		//char value is not void *buf.
		write(fileDes[1], buffer, sizeof(buffer));
	
		write(fileDes[1], "\n", 1);

		cout << "Child will now sleep for 2 seconds" << endl;

		exit(EXIT_FAILURE);

	}else{

		cout << "Parent is running." << endl;

		wait(NULL);

		close(fileDes[1]);
		
		read(fileDes[0], buffer, sizeof(buffer));	

		for(int c = 0; c < sizeof(buffer); c++){

			cout << buffer[c];

			//sleep(1);		
			
		}

		cout << "\n" << endl;

	}

	return 0;

}
