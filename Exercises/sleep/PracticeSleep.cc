#include <unistd.h>
#include <signal.h>

using namespace std;

int main(){
/*
	
	This program won't do anything, until 10

	seconds has passed.

	And the Google tells me it can't wake up

	no matter what, despite the fact that man says

	there is this "signal" that could wake up my computer back.

*/	
	int returnVal = sleep(10);

	return 0;

}
