#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(){

	raise(SIGALRM);
	
	cout << "eek, halp." << endl;

	return 0;

}


