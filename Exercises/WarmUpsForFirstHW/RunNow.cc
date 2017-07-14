#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

main(){

	char argv[] = {"Hello World" ,NULL};

	execl("./RunAfter.o", argv);		

}
