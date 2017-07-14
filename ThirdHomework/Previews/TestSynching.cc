/*

	child read, parent write.

	08:47PM

	And as I have hypothesized, whichever process will go into suspense when the

	they are reading/writing, and there is nothing to read/write from pipe.

*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>
#include <time.h>

using namespace std;

int main(){

	char streamThis[] = "One Two Three Rock and Roll.\n";

	char buffer[strlen(streamThis)];

	int fileDes[2];

	pipe(fileDes);

	int PID = fork();

	if(PID == 0){
		
		close(fileDes[1]);

		cout << "The child should be in suspend because the parent is sleeping." << endl;

		read(fileDes[0], buffer, strlen(streamThis));

		write(STDOUT_FILENO, buffer, strlen(streamThis));					


	}else{

		cout << "The parent process will now go into sleep." << endl;

		close(fileDes[0]);

		sleep(7);

		write(fileDes[1], streamThis, strlen(streamThis));

		wait(NULL);

	}

	return 0;

}
