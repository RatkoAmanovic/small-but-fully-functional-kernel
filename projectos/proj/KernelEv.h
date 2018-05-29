#ifndef __KERNELEV_H_
#define __KERNELEV_H_

#include "include.h"
#include "KernlThr.h"
#include "EventLst.h"
#include "HelpStrc.h"

class PCB;

class KernelEv {
	public:

		friend class KernelThread;

		KernelEv(IVTNo ivtNo);
		~KernelEv();
		void wait();
		void signal();
		unsigned getId();
	private:
		static unsigned ID;
		unsigned id;
		IVTNo ivtNo;
		PCB *myPCB;
		static KernelEvList kernelEventList;
		volatile int value;

		void block();
		void deblock();
};

#endif /* __KERNELEV_H_ */
