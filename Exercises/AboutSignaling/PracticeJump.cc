#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <iostream>

using namespace std;

int main(){

	jmp_buf env;

	int val;
/*

	What the set jump does, is it stores the stack context in the jum_buf data type.

	And it must be used with the combination of longjmp, in order for anything to work.

*/
//At first, setjmp will return 0,
//and setjmp will always return zero when it's returning something right after the call.	
	val = setjmp(env); 
	
	cout << "Val is " << val << endl;

	if(val == 0){
//longjmp will return to the point where the setjmp was.
//The second parameter acts sort of as a status,
//which will overwrite the val value.
//And it is directly stated in the manuel page that
//the program execution continues as if the setjump() has returned
//the value inside the longjmp.
		longjmp(env, 2);

	}	

	return 0;

}

