#include <iostream>
#include <vector> //If I want to use a dynamic array called vector,	
		  //I must use something called


using namespace std;

//:: <- seems like I am requires to use that for some reason.
//Despite the fact that I have declared the vector template,
//how is it the fact that iterator in vector is not
//visible to this program?
//vector<int>::iterator iter1 = vec.begin();
//vector<int>::iterator iter2 = vec.end();

int main(){

	//The learning sources rarely innitialize the things.
	vector<int> myVector;

	myVector.push_back(0);
	myVector.push_back(1);
	myVector.push_back(2);
	myVector.push_back(3);
/*
	
	How I ought the codes below to be?	

	The itr1 and itr2 must have there data types be declared,

	then my question is, why?

	Anyway, ultimately, itr1 and the itr2 will have pointers

	be assigned to them.

*/

	vector<int>::iterator iter1 = myVector.begin(); 
	vector<int>::iterator iter2 = myVector.end();

	cout << *iter1 << endl;
	cout << *iter2 << endl;

	cout << "Vector: ";

	for(int i = 0; i < myVector.size(); i++){

		cout << myVector.at(i) << " ";
	}
	
	cout << endl;

	return 0;

}
