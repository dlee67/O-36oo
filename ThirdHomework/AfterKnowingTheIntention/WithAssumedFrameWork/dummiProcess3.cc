#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){

	for(int c = 0; c < 2; c++){
		cout << "I am dummi3" << endl;
		sleep(1);
	}

}
