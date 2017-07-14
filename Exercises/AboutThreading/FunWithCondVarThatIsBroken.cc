/*

	Look, C++ had their own templates all a long.
	
	However, it's giving me an error saying my g++ compiler is outdated or something.	

*/
#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <unistd.h>

//using namespace std;

void threadFunction(){

	std::cout << "Thread is running" << endl;

	sleep(1);

	std::cout << "Exiting..." << endl;
	
}

int main(){

	std::thread thread1(threadFunction);

	std::thread thread2(threadFunction);

	thread1.join();

	thread2.join();	

	std::cout << "The program has finished." << endl;

	return 0;

}
