#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

	char path[] = "./tempFifo";

	char buffer[100];

	int fileDescriptor = open("tempFifo", O_RDONLY);
	
	read(fileDescriptor, buffer, sizeof(buffer));

	write(STDOUT_FILENO, buffer, sizeof(buffer));

	exit(EXIT_SUCCESS); 

	return 0;

}
