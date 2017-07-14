#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>

using namespace std;

struct C{

	int x;
	int y;
	int z;

};

int main(){

	struct C testing = {1, 3, 7};

	cout << testing.x << endl;

	cout << testing.y << endl;

	cout << testing.z << endl;

	return 0;

}
