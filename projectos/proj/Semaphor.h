#ifndef _semaphor_h_
#define _semaphor_h_

#include "include.h"
#include "HelpStrc.h"

class KernelSem;

class Semaphore {
	public:
		Semaphore (int init=1);
		virtual ~Semaphore ();
		virtual int wait (int toBlock = 1);
		virtual void signal();
		int val () const; // Returns the current value of the semaphore
	private:
		unsigned kernelSemId;
};
#endif
