#include <iostream>
#include <csignal>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

void signalHandler(int sigNum){
	
	cout << "\nABORT!" << endl;
//Now, I just need to resume to the caller.

}
/*

	Raising a signal?

	A signal is a communication to a process,
	
	but instead of being a communication, it feels more like a
	
	road block that kernel must deal with before doing anything else,
	
	while risking reentran behaviors.

*/
int main(){

//That's it man.
	signal(SIGABRT, signalHandler);

	abort();

	while(1){

		sleep(7);

	}

}
