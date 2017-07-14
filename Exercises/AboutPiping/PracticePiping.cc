/*

	Demoing of child reading from the parent seems to be the

	case here.

*/
#include <unistd.h> //For fork() and pipe()
#include <stdlib.h> //For exit()
#include <iostream>
#include <stdio.h> //For perror()
#include <sys/wait.h>
#include <string.h>

#define BUF_SIZE 10

using namespace std;

int main(int argc, char* argv[]){
	//ssize_t is something that is used for return values of the functions.
	//Meaning, it is strictly for the error corrections(?)
	ssize_t numRead;
	
	//Once again, buffer is a designated memory space so that data could travel between
	//places to places.
	char buffer[BUF_SIZE]; 

	int fileDes[2]; //Ultimately, file descriptors(such as cout and cin) will be used for the 
			//processses to communicate with each other.

	//Soon, as soon as the pipe function is called, a pipe is created and the child and the
	//parent process can communicate through pipe.
	//fileDes is passed in so child and the parent knows which file descriptor is used for the 
	//communication to happen.
	pipe(fileDes);

	pid_t PID = fork();

	if(PID == -1){

		perror("fork()");
		exit(EXIT_FAILURE);
	
	}else if(PID == 0){
	//Starting from here, we'll be tackling piping and stuff.
			
	//Close function is used to "close" the file descriptors.
	//It sounds like I am unabling any other inputs or outputs.
	//In this particular if block, close function will return
	//-1, if something goes wrong.
	/*
		if(close(fileDes[1]) == -1){	
		
			perror("close");
			exit(EXIT_FAILURE);					

		}
	*/
	//For now, under the assumption that nothing is going to go wrong,
	//I am going to call close().
		close(fileDes[1]);
	
		while(1){

		//	cout << "\nlooping\n" << endl;
		//So, fileDes[0] is passed in because child is reading something.
		//And buffer is passed in because buffer, in this case, is the 
		//beginning of the address.
		//BUF_SIZE is passed in because it's the amount of bytes I would like
		//to read.
		//According to the documentation, and the book I am reading about,
		//seems like read() will print out everything those are being read in the
		//array.
		//Okay, read() reads byte by byte,	
			numRead = read(fileDes[0], buffer, sizeof(buffer));

		//According to the Stack Overflow, write() will write out to the file
		//descriptor specified by the first argument.
			write(STDOUT_FILENO, buffer, sizeof(buffer));		
		//	if(write(STDOUT_FILENO, buffer, numRead) != numRead){
		//		exit(EXIT_FAILURE);
		//	}		
			if(numRead == -1){
				perror("read");
				exit(EXIT_FAILURE);
			}	
		//The if block below is suppose to signify the end of the file,
		//but I have a hard time grasping why.
		//Seems like it's not clearly catching null ter
			if(numRead == 0){
				cout << "numRead == 0 reached" << endl;				
				break;
			}
		//According to the book, I will have to use write function again
		//to write things to the command prompt...
		//well, makes sense, because computer needs someone to
		//tell it what to do,
		//well, more specifically, because I need to tell the compiler to do
		//what I want it to do, within in the boundary of what it understands.

			

		}

		cout << "\nOut of the loop\n" << endl;

		//I am telling the kernel, by passing in STDOUT_FILENO(which indicates that
		//whatever I will be passing in will be through output on the console),
		//that \n needs to be printed out, which is indicated by the "\n".
		//Finally, the third argument tells the kernel that I only want a single 
		//byte to be printed out.
		//to add on to the epiphany, system calls are not communication through the
		//source code(more accurately, object files), but it is to the kernel; meaning,
		//asking questions such as, "which component of the source code is write() 
		//talking with?" has no answer, because write() is talking with the kernel.
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);

	//Else block is dedicated for the parent processes to write things in.
	}else{
		close(fileDes[0]);
		//The if block below tells the parent process to pipe everything
		//to the child process; however, counter intuitively, the writing procedure
		//is done in an instance, which does not require any sort of iteration
		//be gone through.
		//fileDes[1] is passed in so that kernel knows I am writing things,
		//and argv[1] is passed in for the second argument, I think because 
		//second argument act as something that I will pass in to the receving end of 
		//the pipe.
		//Finally, the third argument, strlen(argv[1]), is the amound of byte the 
		//write will write off to the receiving end of the pipe.
		if(write(fileDes[1], argv[1], strlen(argv[1])) != strlen(argv[1])){
			exit(EXIT_FAILURE);	
		}

		//After writing everything to the pipe,
		//parent will have to wait for the child to process all the strings those have
		//passed in.
		wait(NULL);
		
		exit(EXIT_SUCCESS);

	}

	return 0;

}
