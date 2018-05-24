#ifndef _thread_h_
#define _thread_h_

#include "include.h"
#include <iostream.h>

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
	public:
		 void start();
		 void waitToComplete();
		 virtual ~Thread();
		 static void sleep(Time timeToSleep);
	protected:
		 friend class PCB;
		 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
		 virtual void run() {}
	private:
		 PCB* myPCB;
};

void dispatch ();

#endif
