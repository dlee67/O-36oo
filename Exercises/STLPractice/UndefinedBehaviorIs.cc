#include <iostream>
#include <vector>

using namespace std;

int main(){

	vector<int> VectorName;

	VectorName.push_back(2);
	VectorName.push_back(3);

	//The line below doesn't throw an exception,
	cout << VectorName[3] << endl;

	//while this one does during the run time.
	cout << VectorName.at(3) << endl;
	
	//What's going on?

}
