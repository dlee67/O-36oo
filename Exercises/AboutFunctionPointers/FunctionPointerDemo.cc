#include <iostream>

using namespace std;

void VoidFunction(){

	cout << "Void Function" << endl;

}

void VoidFunctionTwo(){

	cout << "Void function two" << endl;

}

int main(){

	void (*PointerName) ();
	//Not even without dereferencing the VoidFuntion,
	//I was able to use the full functionality of the 
	//VoidFunction.
	PointerName = VoidFunction;
	//The line below is the demo.
	PointerName();

	PointerName = VoidFunctionTwo;

	PointerName();

}


