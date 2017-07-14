#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv){

	cout << "First part of the assignment is executing.\n" << endl;

	cout << "The value of iterCount should be: 5" << endl;

//I shouldn't worry about the return status for now,
//I need to use the exec() to see if the intended values
//are being passed in.
//To see if the getpid() streamed out without a problem.
/*

	Was not behaving as I intended to, but after writing in the directive, 
	#include <sys/types.h> and #include <unistd.h>, the program started to
	work.

*/
//As of now, can't really see why I would need the line below.
//	cout << getpid() << endl;

/*

	The code below's purpose is to grab the first character streamed through 

	the entry point. 

	Innitially, char iterCount = argv[0]; was the line of code, but
	
	it should actually be a *argv[0], instead of argv[0] because it is

	mandatory for me to either state &(ampersand for the address), or
	
	*(asterisk for dereference) for the pointer data types.

	The below two line do just that.

	
	Now, I need to use exec().	

*/
	char iterCount = *argv[0]; 

	cout << iterCount << " That's the value that was passed in... \n" << endl;

/*

	Now I have to convert whatever character I passed in to int data type.

	Assume toInt is the number of iterations I want.

	Seems like the iterations are working.

	I've confirmed that expression can be text streamed.

	Now, I just need to print out the demanded strings.

	PID and the incrementing iteration.

*/

	char exampleChar = '5';
	int toInt = (int)exampleChar - '0';

	cout << toInt << '\n' << endl;

	for(int x = 0; x < toInt; x++){

		cout << "Process: "<< getpid() << " " << x + 1 << endl;

	}	

//I need the first program to return the status.
}
