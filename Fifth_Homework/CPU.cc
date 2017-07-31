/*
	Name: Dong(Bob) Lee
	Date: 07/09/17
	Got Helped From: Dalton Wiebold, Brian Von Behren, Eli Skaronea, and Ryan 
*/
#include <iostream>
#include <list>
#include <iterator>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define NUM_SECONDS 20
//The buffer size shouldn't be always 32;
#define BUFFER_SIZE 32

// make sure the asserts work
#undef NDEBUG
#include <assert.h>

#define EBUG
#ifdef EBUG
#   define dmess(a) cout << "in " << __FILE__ << \
    " at " << __LINE__ << " " << a << endl;

#   define dprint(a) cout << "in " << __FILE__ << \
    " at " << __LINE__ << " " << (#a) << " = " << a << endl;

#   define dprintt(a,b) cout << "in " << __FILE__ << \
    " at " << __LINE__ << " " << a << " " << (#b) << " = " \
    << b << endl
#else
#   define dprint(a)
#endif /* EBUG */

using namespace std;

enum STATE { NEW, RUNNING, WAITING, READY, TERMINATED };

/*
** a signal handler for those signals delivered to this process, but
** not already handled.
*/
void grab (int signum) { dprint (signum); }

// c++decl> declare ISV as array 32 of pointer to function (int) returning
// void
void (*ISV[32])(int) = {
/*        00    01    02    03    04    05    06    07    08    09 */
/*  0 */ grab, grab, grab, grab, grab, grab, grab, grab, grab, grab,
/* 10 */ grab, grab, grab, grab, grab, grab, grab, grab, grab, grab,
/* 20 */ grab, grab, grab, grab, grab, grab, grab, grab, grab, grab,
/* 30 */ grab, grab
};

struct PCB
{
    STATE state;
    const char *name;   // name of the executable
    int pid;            // process id from fork();
    int ppid;           // parent process id
    int interrupts;     // number of times interrupted
    int switches;       // may be < interrupts
    int started;        // the time this process started
    int pipeID;
    int kernelToProcess[2];
    int processToKernel[2];
    int fileDesID;
};

/*
** an overloaded output operator that prints a PCB
*/
ostream& operator << (ostream &os, struct PCB *pcb)
{
    os << "state:        " << pcb->state << endl;
    os << "name:         " << pcb->name << endl;
    os << "pid:          " << pcb->pid << endl;
    os << "ppid:         " << pcb->ppid << endl;
    os << "interrupts:   " << pcb->interrupts << endl;
    os << "switches:     " << pcb->switches << endl;
    os << "started:      " << pcb->started << endl;
    return (os);
}

/*
** an overloaded output operator that prints a list of PCBs
*/
ostream& operator << (ostream &os, list<PCB *> which)
{
    list<PCB *>::iterator PCB_iter;
    for (PCB_iter = which.begin(); PCB_iter != which.end(); PCB_iter++)
    {
        os << (*PCB_iter);
    }
    return (os);
}

PCB *running;
PCB *idle;
list<PCB *> new_list;
list<PCB *> processes;
int sys_time;

/*
**  send signal to process pid every interval for number of times.
*/
void send_signals (int signal, int pid, int interval, int number)
{
    dprintt ("at beginning of send_signals", getpid ());
    for (int i = 1; i <= number; i++)
    {
        sleep (interval);
        dprintt ("sending", signal);
        dprintt ("to", pid);
        if (kill (pid, signal) == -1)
        {
            perror ("kill");
            return;
        }
    } dmess ("at end of send_signals");
}

struct sigaction *create_handler (int signum, void (*handler)(int))
{
    struct sigaction *action = new (struct sigaction);
    action->sa_handler = handler;

    if (signum == SIGCHLD)
    {
        action->sa_flags = SA_NOCLDSTOP;
    }
    else
    {
        action->sa_flags = 0;
    }

    sigemptyset (&(action->sa_mask));

    assert (sigaction (signum, action, NULL) == 0);
    return (action);
}

PCB* choose_process(){
	if(!processes.empty()){				
		PCB* returnThis = processes.front();
		if(returnThis->state == READY){
			processes.pop_front();
			char* passingFileDes = (char*)returnThis->fileDesID;
//////////////////////////////////////////////////////////////////editing			
			char passNumber[BUFFER_SIZE]; sprintf(passNumber, "%d", returnThis->fileDesID);
			returnThis->pid = fork();
			if(returnThis->pid == 0){
				if(returnThis->pid == 0){
					if((execl(returnThis->name, passNumber, (char*)NULL)) == -1){
						perror("execl");
					}
				}
			}
/////////////////////////////////////////////////////////////////editing			
			returnThis->ppid = getpid();
			returnThis->started = sys_time;			
			returnThis->state = RUNNING;	
			processes.push_back(returnThis);
			return returnThis;
		}else if(returnThis->state == TERMINATED){				
			processes.pop_front();
			return idle;		
		}
		return returnThis;
	}else{		
		list<PCB*>::iterator iter;
		for(iter = processes.begin(); iter != processes.end(); iter++){
			PCB* pointed = *iter;			
			if(pointed->state == READY){
				return pointed;			
			}
		}
		return idle;	
	}
	return idle;
}

void scheduler (int signum)
{
	assert (signum == SIGALRM);
 	sys_time++;	
	PCB* tocont = choose_process();
	running = tocont;
	running->switches++;
	running->interrupts++;	
	if(kill(tocont->pid, SIGCONT) < 0){
		perror("kill");
	}
}

void process_done (int signum)
{
    assert (signum == SIGCHLD);
	int status, cpid;
    cpid = waitpid (-1, &status, WNOHANG);
	dprintt ("in process_done", cpid);
	running->state = TERMINATED;
	running->pid = cpid;
	cout << running << endl;
	processes.pop_front();
	processes.push_back(running);
	running = idle;

    if  (cpid == -1)
    {
        perror ("waitpid");
    }
    else if (cpid == 0)
    {
        if (errno == EINTR) { return; }
        perror ("no children");
    }
    else
    {
        dprint (WEXITSTATUS (status));
    }
}

/*
** stop the running process and index into the ISV to call the ISR
*/
void ISR (int signum)
{

    if (kill (running->pid, SIGSTOP) == -1)
    {	perror ("kill"); return; }
    dprintt ("stopped", running->pid);
    ISV[signum](signum);
}

void trap_handler (int signum){
/*
	
	Something about emptying out the buffer.

*/
	cout << "\n\n";
	cout << "Trap handler was called." << endl;	

	char buffer[BUFFER_SIZE];

	if((read((running->fileDesID) + 2, buffer, BUFFER_SIZE)) == -1){
		perror("read");
	}
	if((write(1, buffer, strlen(buffer))) == -1){ perror("write"); }
	cout << " received." << endl;

//Operation for l.
/*
	07/24/17
	I am not sure if it's the correct behavior, but when ./CPU.o Child.o dummi.o dummi2.o 
	are typed in the bash, dummi2.o shows up twice, and Child.o shows up only once as the processes
	in the processes list.
*/
	list<PCB *>::iterator iter;
	if(buffer[0] == 'l'){
		cout << "listing processes now: " << endl;
		for(iter = processes.begin(); iter != processes.end(); iter++){
			cout << *(iter) << endl;	
		}
	}	

//Operation for s is suppose to show here.	
/*
	07/24/17
	Doesn't seemed show any extreme irregularity.
*/
	if(buffer[0] == 's'){
		cout << "System time request received." << endl;
		cout << "System time as of now: " << sys_time << endl;
	}

	if(buffer[0] == 'p'){
		cout << "Printing the list of processes and the system time.\n" << endl;
		for(iter = processes.begin(); iter != processes.end(); iter++){
			cout << *(iter) << endl;	
		}
		cout << "System time as of now: " << sys_time << endl;
	}

	cout << "\n\n";

	char* r = "r";
	cout << "Parent sending received signal: r" << endl;
	cout << "sending signal to: " << running->pid << endl;
	if((write((running->fileDesID) + 1, r, strlen(r))) == -1){
		perror("write");	
	} 
	if(kill(running->pid, SIGUSR1) == -1){
		perror("kill");	
	}

	cout << "\n\n";
}
/*
** set up the "hardware"
*/
void boot (int pid)
{
    ISV[SIGALRM] = scheduler;       create_handler (SIGALRM, ISR);
    ISV[SIGCHLD] = process_done;    create_handler (SIGCHLD, ISR);
    ISV[SIGTRAP] = trap_handler;    create_handler (SIGTRAP, ISR);
	
    // start up clock interrupt
    int ret;
    if ((ret = fork ()) == 0)
    {
        // signal this process once a second for three times
        send_signals (SIGALRM, pid, 1, NUM_SECONDS);

        // once that's done, really kill everything...
        kill (0, SIGTERM);
    }

    if (ret < 0)
    {
        perror ("fork");
    }
}

void create_idle ()
{
    int idlepid;
    if ((idlepid = fork ()) == 0)
    {
        dprintt ("idle", getpid ());

        // the pause might be interrupted, so we need to
        // repeat it forever.
        for (;;)
        {
            dmess ("going to sleep");
            pause ();
            if (errno == EINTR)
            {
                dmess ("waking up");
                continue;
            }
            perror ("pause");
        }
    }
    idle = new (PCB);
    idle->state = RUNNING;
    idle->name = "IDLE";
    idle->pid = idlepid;
    idle->ppid = 0;
    idle->interrupts = 0;
    idle->switches = 0;
    idle->started = sys_time;
}

int main (int argc, char **argv)
{
    int pid = getpid();
    dprintt ("main", pid);

    sys_time = 0;

	int n = 1;
	int pipeDesIndex = 3;
	while(argv[n]){
		PCB* newProcess = new (PCB);
		newProcess->name = argv[n];
		newProcess->state = READY;
								//Since, the pipeDesIndex is being updated,
		newProcess->fileDesID = pipeDesIndex;
		if((pipe(newProcess->kernelToProcess) || pipe(newProcess->processToKernel)) == -1){
			perror("pipe");
		}
		if(
		/* By the tuples(like, 34 56 78 9'10' and so on....)
		   where pipeDesIndex is always interval of 4.	*/
		dup2(newProcess->fileDesID, newProcess->kernelToProcess[0]) ||
		dup2((newProcess->fileDesID) + 1, newProcess->kernelToProcess[1]) ||
		dup2((newProcess->fileDesID) + 2, newProcess->processToKernel[0]) ||
		dup2((newProcess->fileDesID) + 3, newProcess->processToKernel[1]) == -1){
			perror("dup2");
		} 
						//thus, the fileDesID is being updated.
		pipeDesIndex = (newProcess->fileDesID) + 4;
		new_list.push_back(newProcess);		
		n++;	
	}
	while(new_list.size() != 0){
		PCB* newProcess = new (PCB);
		newProcess = new_list.back();
		newProcess->state = READY;
		processes.push_back(newProcess);
		new_list.pop_back();
	}
    boot (pid);
    // create a process to soak up cycles
    create_idle ();
    running = idle;

    cout << running;

    // we keep this process around so that the children don't die and
    // to keep the IRQs in place.
    for (;;)
    {
        pause();
        if (errno == EINTR) { continue; }
        perror ("pause");
    }
}
