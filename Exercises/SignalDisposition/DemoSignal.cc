#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

//Function pointer prototype for a signaling.
//passes in sig number(which really is just a signal macro)
//and handler is the address of the function should be called when
//this signal is delivered(to a process, so process could act accordingly);
//at the same time, the handler function takes in an int argument(meaning, there is a function pointer
//in a function pointer).
//Bottom line is, it takes a signal, and an int.
void (*signal(int sig, void (*handler)(int)))(int);

