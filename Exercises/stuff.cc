#include <unistd.h>
#include <stdlib.h>
#include <alloca.h>
#include <iostream>

using namespace std;

int* returnArray(){
	
	//If I want the malloc to return a pointer other than a void,
	//then I need to type cast it like the below.
	//int* testArray = (int*)malloc(sizeof(int)*4);


	//When memory is allocated, then that allocated memory can be treated like
	//an array.
	//testArray[0] = 1;

	//cout << testArray[0] << endl;

	int* testArray = (int*)alloca(sizeof(int)*4);

	return testArray;

}

int main(){

	int *foo = new int[5];

	cout << foo[0] << endl;

	//So, if I want to assign a value to an array box.
	foo[0] = 1;
	
	cout << foo[0] << endl;

	int* supposeToFail = returnArray();
	/*
	
		So, seems like pointers don't get ridden of when the stackframe pops off.		

	*/	
	cout << "\nExecuting returnArray() " << returnArray() << endl;

	return 0;

}
