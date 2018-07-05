#include "Semaphor.h"
#include "include.h"
#include "KernlSem.h"
#include "PCB.h"
#include "CSwitch.h"
#include "HelpStrc.h"
#include "KernlThr.h"

Semaphore::Semaphore(int init) {
	Helper* helper = new Helper();
	helper->function = eventConstruct;
	helper->init = init;
	#ifndef BCC_BLOCK_IGNORE
		CONSTRUCTOR_SYSTEM_CALL;
	#endif
	kernelSemId = helper->id;
	delete helper;
}

Semaphore::~Semaphore() {
	Helper* helper = new Helper();
	helper->function = semaphoreDestruct;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

int Semaphore::wait(int toBlock) {
	int temp;
	if(!toBlock) {
		if (val()<=0)
			return -1;
	}
	Helper* helper = new Helper();
	helper->function = eventWait;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	temp = helper->init;
	delete helper;
	return temp;
}

void Semaphore::signal() {
	Helper* helper = new Helper();
	helper->function = semaphoreSignal;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

int Semaphore::val() const {
	int temp;
	Helper* helper = new Helper();
	helper->function = semaphoreValue;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	temp = helper->init;
	delete helper;
	return temp;
}
