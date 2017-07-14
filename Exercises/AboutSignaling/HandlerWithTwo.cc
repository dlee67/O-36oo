#include <signal.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void sigHandler(int sig){

	if(sig == SIGINT){

		cout << "\nPressed Ctrl + C" << endl;

	}else if(sig == SIGQUIT){

		cout << "\nPressed Ctrl + \\" << endl;

	}

}

int main(){

	signal(SIGINT, sigHandler);

	signal(SIGQUIT, sigHandler);	
	
	while(1){

		sleep(3);

	}

	return 0;

}
