/*
	
	This program demonstrates how the signal handler behaves with the combination of

	the jump functions.

*/
#include <iostream>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

jmp_buf envStack;

void signalHandler(int sigNum){

	if(sigNum == SIGINT){

		cout << "\nInterrupt has occured." << endl;

	}
//Long jump will move the PC to flowAlterer, and have the setjmp() return the 
//second argument of the function below, which is 1.
	longjmp(envStack, 1);	

}

int main(){

//jmp_buf envStack;
//So, flowAlterer will have to be used to change the course of the
//logic.
//Since, the longjmp will have the setjmp() return the value of the
//second parameter of longjmp, I will have to use that; meaning...
	int flowAlterer = setjmp(envStack);

//When setjmp is called for the first time, it returns 0.

	signal(SIGINT, signalHandler);

	if(flowAlterer == 0){

		while(1){

			sleep(1);
			cout << "\nWaiting for the interrupt." << endl;		

		}	

	}else if(flowAlterer == 1){

		cout << "\nThe signal handler has been finished." << endl;

	}

}
