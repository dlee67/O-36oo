#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
/*
	
	Yes, we can communicate with the forked child().

*/
	int letChild = fork();
	
	if(letChild == 0){
		execl("dummiProcess.o", NULL);
	}	

	sleep(1);
	kill(letChild, SIGTERM);

	return 0;
	
}
