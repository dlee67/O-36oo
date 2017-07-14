#include <iostream>

using namespace std;

void display(){
	
	cout << "I am a function that displays things." << endl;

}

void displaySum(int x){

	cout << x + 5 << endl;

}

int main(){

	//Perhaps, function pointers are used in order to use multiple functions with
	//single statement.

	//*FPointer is a pointer that takes no argument.
	void (*FPointer)();

	//*foo is function pointer that takes int as an argument.
	void (*foo)(int);

	//Does not need a parameter for the assigining pointers.... what in the world.
	//Was previously FPointer = display;
	FPointer = &display;

	FPointer();
		
	//Was previously foo = displaySum;
	foo = &displaySum;

	foo(5);

	//Yeah, a bizzare conclusion, where a varaible that was declared as a function pointer can
	//literally be a function, by assigning function to it.

}
