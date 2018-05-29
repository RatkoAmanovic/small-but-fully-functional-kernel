#ifndef __KERNLSEM_H_
#define __KERNLSEM_H_

#include "include.h"
#include "SemapLst.h"
#include "BlckList.h"
#include "HelpStrc.h"

class KernelSem {
	public:

		friend class KernelThread;

		KernelSem(int init);
		~KernelSem();
		int wait ();
		void signal();
		int val () const; // Returns the current value of the semaphore
		unsigned getId();
	private:
		static unsigned ID;
 		volatile unsigned id;

		int value;
		BlockList blockedList;

		static KernelSemList kernelSemaphoreList;

		void block();
		void deblock();
};

#endif /* __KERNLSEM_H_ */
