#ifndef __KERNLTHR_H_
#define __KERNLTHR_H_

#include "include.h"

struct Helper;
class PCB;

class KernelThread {
public:
	KernelThread();
	~KernelThread();
	static void inic();
	static void run();


	static void interrupt switchToKernel(...);
	static KernelThread* getKernelThread();

	static void threadConstruct();
	static void threadStart();
	static void threadWaitToComplete();
	static void threadSleep();
	static void threadDispatch();
	static void threadResumeAll();
	static void threadDestruct();
	static void eventConstruct();
	static void eventWait();
	static void eventSignal();
	static void eventDestruct();
	static void semaphoreConstruct();
	static void semaphoreWait();
	static void semaphoreSignal();
	static void semaphoreValue();
	static void semaphoreDestruct();
private:
	static void interrupt switchToUser(...);
	static volatile int kernelThreadRequestedSwitch;
	static volatile Helper* helper;
	static volatile PCB* myPCB;
	static volatile Function* functions;
	static KernelThread* kernelThread;
	static const int SWITCH_TO_KERNEL_ENTRY;
	static const int SWITCH_TO_USER_ENTRY;
};

#endif /* KERNLTHR_H_ */
