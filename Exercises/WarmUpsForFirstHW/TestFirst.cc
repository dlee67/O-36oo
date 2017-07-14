#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(){

	cout << "This program will test if the right value is being passed in to First.cc.\n" << endl;
	
	//execl() function must pass in the executable,
	//doesn't make any sense if execl("./First.cc", "5"); were to execute.	
	execl("./First.o", "5");

	return 0;

}
