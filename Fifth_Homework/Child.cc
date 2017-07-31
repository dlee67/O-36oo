#include <unistd.h> //For fork() and pipe()
#include <stdlib.h> //For exit()
#include <iostream>
#include <stdio.h> //For perror()
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

int lock = 1;

using namespace std;

void signal_handler(int signum){

	cout << "Lock realesed." << endl;
	lock = 0;
}

int main(int argc, char** argv){	

	cout << "\n\n";

	signal(SIGUSR1, signal_handler);
	cout << getpid() << " is starting, and have received: " << *(argv[0]) << " as the fileDesID." << endl;	
	int fileDes = atoi(argv[0]);
	char buffer[32];

	cout << "\n";
	char* message = "l\0";	
	if(write((fileDes + 3), message, strlen(message) + 1) == -1){ perror("write"); }

	cout << getpid() << " is SIGTRAP." << endl;
	kill(getppid(), SIGTRAP);


	while(lock){ sleep(1); /* WOOOOHAHAHAH!!! */ }


	if(read(fileDes, buffer, BUFFER_SIZE) == -1){
		perror("read");
	}
	if(write(1, buffer, strlen(buffer)) == -1){
		perror("write");
	}
	cout << " was received from the parent.";
	cout << "\n\n";
	//cout << getpid() << " received: ";
}
