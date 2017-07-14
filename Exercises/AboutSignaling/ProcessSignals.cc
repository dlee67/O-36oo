#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(){

//From the demonstration in stack overflow, after searching "kill child process"
//in google, on the second parameter, I passed in a macro instead of an int, 
//as the manual page have stated.
	kill(getpid(), SIGKILL);

	cout << "eek help" << endl;

	return 0;

}
