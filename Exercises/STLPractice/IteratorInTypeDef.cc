#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main(){
/*

	According to the Mr.Luke's suggestion, 
	
	typedef should be used if I really want to use the 

	vector<int>::iterator in it's own type.

*/
	typedef vector<int>::iterator iter;
	
	iter iter1;

	iter iter2;

	vector<int> vector;

	vector.push_back(0);

	vector.push_back(1);
	
	vector.push_back(2);

	//iter1 = vector.begin();

	iter2 = vector.end();

	for(iter1 = vector.begin(); iter1 != iter2; iter1++){

		cout << *iter1 << endl;

	}

}
