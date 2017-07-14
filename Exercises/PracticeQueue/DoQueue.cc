#include <deque>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int main(){

	deque<int> numbers;

	numbers.push_back(0);

	numbers.push_back(1);

	numbers.push_back(2);

	numbers.push_back(3);

	numbers.push_back(4);

	deque<int>::iterator iter1;
	
	deque<int>::iterator iter2;
	
	for(iter1 = numbers.begin(), iter2 = numbers.end(); iter1 != iter2; iter1++){

		cout << *iter1 << endl;	

	}

	/*

		Nothing out of ordinary that the deque would not work.

	*/

	return 0;

}
