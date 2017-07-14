#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void signalHandler(int sigNum){

	if(sigNum == SIGINT){

		cout << "\nA signal handler has been called" << endl;

	}

}

int main(){

	signal(SIGINT, signalHandler);

	cout << "\nPC has returned after signal" << endl;

	while(1){

		sleep(1);

		cout << "\nPC has returned to the loop" << endl;

	}

	return 0;
	
}
