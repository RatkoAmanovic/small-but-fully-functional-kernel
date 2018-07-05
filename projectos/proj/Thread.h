#ifndef _thread_h_
#define _thread_h_

#include "include.h"
#include <iostream.h>

class PCB; // Kernel's implementation of a user's thread

class Thread {
	public:
		 void start();
		 void waitToComplete();
		 virtual ~Thread();
		 static void sleep(Time timeToSleep);
		 unsigned getId();
		 void resumeAll();
	protected:
		 friend class PCB;
		 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
		 Thread (int i, int j, int k);
		 virtual void run() {}

	private:
		 volatile unsigned pcbId;

		 static void wrapper(Thread* running);
};

void dispatch ();

#endif
