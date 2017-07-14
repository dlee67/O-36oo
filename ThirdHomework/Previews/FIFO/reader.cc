#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF 1024

int main(){

	sleep(3);

	int fd;

	char* myfifo = "./myfifo";
	char buf[MAX_BUF];

	fd = open(myfifo, O_RDONLY);
	read(fd, buf, MAX_BUF);
	write(STDOUT_FILENO, buf, MAX_BUF);

	close(fd);

	exit(EXIT_SUCCESS);

	return 0;

}
