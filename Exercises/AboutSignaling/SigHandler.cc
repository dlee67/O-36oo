#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void sigHandler(int signo){

	if(signo == SIGINT){

		cout << "\nlol, ctl + c" << endl;

	}else if(signo == SIGQUIT){

		cout << "\nYou cannot quit!" << endl;
	
	}

}

int main()
{

	//if(signal(SIGINT, sigHandler) == SIG_ERR)
	//	cout << "Where is the interrupt?" << endl;

	/*
	
		I am guessing soon as the program counter runs over the signal(),

		it prepares for the certain keyboard press(more formally, keyboard interrupt).

	*/

	signal(SIGINT, sigHandler);

//So, the statement below is me telling the kernel to, "prepare for a SIGQUIT keyboard press?"
	//(more formaly, keyboard interrupt).
	//I don't know if my hypothesis was concretely proven, but
	//yes, behaviorally, seems like that's what's happening.
	signal(SIGQUIT, sigHandler);	

	while(1){

		//If the above hypothesis is true, I am guessing	
		//it wouldn't matter if the signal() function is here.
		//signal(SIGINT, sigHandler);

		sleep(1);
	
	}

	return 0;

}
