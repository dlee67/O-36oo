#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){

/*

	The context below is that, if the code underneath works,

	but if I had a map, instead of vector, then I can't iterate

	through the elements with indices(maps have keys).

*/
	vector<string> names;

//Traditionally, we would use for loop with the incrementing index,
//but we can use the iterator.
//Then what is the iterator?
//Iterator is a pointer, and it is designed so that it will point to the
//each elements in sort of a container.
//What is a container?
//It's a term used in order to describe things like array, or a vector.

	vector<string>::iterator iterator;

	names.push_back("Peter");
	names.push_back("CodingMadeEasy");

//iterators behave just like any other pointers;
//thus, incrementing an iterator will make it point to the next element,
//which can be used to dereference, or return the address of what it's pointing.
	for(iterator = names.begin(); iterator != names.end(); iterator++){	

		cout << *iterator << endl;
	
	}
	

}
