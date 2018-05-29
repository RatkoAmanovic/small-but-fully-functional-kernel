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
		helper->stackSegment = FP_SEG(this);
		helper->stackOffset = FP_OFF(this);

		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	kernelSemId = helper->id;
	delete helper;
}

Semaphore::~Semaphore() {
	Helper* helper = new Helper();
	helper->function = semaphoreDestruct;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
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
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	temp = helper->init;
	delete helper;
	return temp;
}

void Semaphore::signal() {
	Helper* helper = new Helper();
	helper->function = semaphoreSignal;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	delete helper;
}

int Semaphore::val() const {
	int temp;
	Helper* helper = new Helper();
	helper->function = semaphoreValue;
	helper->id = kernelSemId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	temp = helper->init;
	delete helper;
	return temp;
}
