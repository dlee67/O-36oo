#include <string>
#include <iostream>

using namespace std;

int main(){

/*

	int house = 5;

	int* pointer = 	&house;

	int** pointerpointer = &pointer;
*/
//I really should ask about the arrays and pointers' interactions.

//In my understanding, the line below will allocate five blocks of memory,
//somewhere in the memory.
	int houses[] = {1,2,3,4,5};

	int* housepointer = &houses; //In my understanding, I am point to the
				     //beginning of the house.

//And the line below will point to the memory address, where the
//housepointer identifier resides.
	int** pointerpointerhouse = &housepointer;

	

}


