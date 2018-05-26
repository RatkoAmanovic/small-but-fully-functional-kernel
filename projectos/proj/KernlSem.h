#ifndef __KERNLSEM_H_
#define __KERNLSEM_H_

#include "BlckList.h"

class KernelSem {
	public:
		KernelSem(int init);
		~KernelSem();
		int wait ();
		void signal();
		int val () const; // Returns the current value of the semaphore
	private:
		int value;
		BlockList blockedList;

		void block();
		void deblock();
};

#endif /* __KERNLSEM_H_ */
