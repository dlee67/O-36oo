/*

	My hypothesis is that the program will break after I comment out the sleep because

	the synchronization happens because of the sleep.

	07:40PM

	but it didn't; therefore, I am guessing the synching happens from the close.

	07:41PM
		
	Yes, the synching is happening from the close(), which, I believe, it implies that

	the child processes are sequentially happening no matter what.

	07:44PM

	Actually, I completely don't know.

	08:00PM 
	
	Later found out that read() suspends the process, until there is something to read from the pipe.

*/
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h> 
#include <sys/wait.h>
#include <string.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv){

	int fileDes[2];

	int dummy;

	printf("%s Parent started\n", "time");

	pipe(fileDes);

	for(int j = 1; j < argc; j++){

		switch(fork()){

			case 0:	
				close(fileDes[0]);

				sleep(5);

				printf("%s Child %d (PID=%ld) closing pipe\n", "time", j, (long)getpid());

				exit(EXIT_SUCCESS);

			default:

				break;

		}

	}

	close(fileDes[1]);

	read(fileDes[0], &dummy, 1);

	exit(EXIT_SUCCESS);

	return 0;

}
