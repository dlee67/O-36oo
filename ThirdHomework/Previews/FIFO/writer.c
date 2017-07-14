/*

	I had a single problem, it was about FIFO, and it was a problem rising from less than 20 lines of code; however,
	
	it took more than 4 hours to solve it.

	
	Anyways,

	having the fork() above the mkfifo was the answer for the problem of writer executable halting.

	The reason is because after the mkfifo is opened, for writer only, the processor that opened it goes in halt,

	until there is a process that opens the same mkfifo that was mentioned above, with the read only.


	Thus, having the execl above the mkfifo was the correct answer.

*/
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	int fd;
	char *myfifo = "./myfifo";

	int PID = fork();	
	
	if(PID == 0){

		execl("./reader.o", "reader", (char*)NULL);

	}

	mkfifo(myfifo, 0777);
	fd = open(myfifo, O_WRONLY);	

	write(fd, "Rock and roll baby\0", sizeof("Rock and roll baby"));
	close(fd);
	unlink(myfifo);

	return 0;

}
