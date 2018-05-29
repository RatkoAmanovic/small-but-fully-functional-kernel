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
	void run();

	static void interrupt switchDomain(...);
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
	static volatile int kernelThreadRequestedSwitch;
	static volatile int inKernel;
	static volatile Helper* helper;
	static volatile PCB* myPCB;
	static volatile Function* functions;
	static KernelThread* kernelThread;
	static const int SWITCH_ENTRY;
};

#endif /* KERNLTHR_H_ */
