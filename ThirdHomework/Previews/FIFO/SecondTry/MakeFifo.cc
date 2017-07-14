#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	char path[] = "./tempFifo";
		
	mkfifo(path, 0777);

	int fileDes = open("tempFifo", O_WRONLY);

	int makeProcess = fork();

	if(makeProcess == 0){

		execl("./OpenFifo.o", "OpenFifo", (char*)NULL);

	}

	write(fileDes, "Lulz", sizeof("Lulz"));
	
	sleep(10);

	exit(EXIT_SUCCESS);

	return 0;

}
