/*

	I am playing around with pointers.

*/
#include <string>
#include <iostream>

using namespace std;

int main(){

	int a = 5;

	int* b = &a;
	
	cout << &a << "<- address of the a." << endl;

	cout << &b << "<- address of the pointer b." << endl;

}
