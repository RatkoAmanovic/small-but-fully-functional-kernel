#ifndef __KERNELEV_H_
#define __KERNELEV_H_

#include "include.h"

class PCB;

class KernelEv {
	public:
		KernelEv(IVTNo ivtNo);
		~KernelEv();
		void wait();
		void signal();
	private:
		IVTNo ivtNo;
		PCB *myPCB;
		volatile int value;

		void block();
		void deblock();
};

#endif /* __KERNELEV_H_ */
