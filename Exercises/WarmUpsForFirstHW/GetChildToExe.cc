/*

	This program will call a child process,
	and that child process will execute a new program.

*/
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(){

	cout << "GetChildToExe.o is running." << endl;

	int PID = fork(); //If child process, PID has 0.
			  //fork() returns twice.
	
	//When I write in {"This has been passed.", NULL};,
	//the compiler will give me an error saying, "too many innitializer for char[]."
	char argString[] = {"The String has been passed.\0"};

	if(PID == 0){

		cout << "Child is being executed." << endl;

		execl("./Exe.o", argString);
	
	}

	return 0;

}

