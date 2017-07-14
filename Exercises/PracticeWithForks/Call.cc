#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

main(int argc, char** argv){

	char x = *argv[0];

	int y = x - '0';

	cout << "Intended exit status is: " << y << endl;

	exit(y);
}
