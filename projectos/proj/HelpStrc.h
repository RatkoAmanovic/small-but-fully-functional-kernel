#ifndef __HELPSTRC_H_
#define __HELPSTRC_H_

#include "include.h"
#include <dos.h>
#include "KernlThr.h"

enum Functions {
	threadConstruct, threadStart, threadWaitToComplete, threadSleep,
	threadDispatch, threadResumeAll, threadDestruct ,
	eventConstruct,
	eventWait, eventSignal, eventDestruct, semaphoreConstruct,
	semaphoreWait, semaphoreSignal, semaphoreValue, semaphoreDestruct

};

struct Helper {

	friend class Thread;
	friend class KernelThread;

	Functions function;
	StackSize stackSize;
	Time timeSlice;
	unsigned id;
	unsigned stackSegment;
	unsigned stackOffset;
	IVTNo ivtNo;
	int init;

};


static void systemCall(Helper* helper){
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);
		asm push cx;
		asm push dx;

		asm mov cx,helperSegment;
		asm mov dx,helperOffset;
	#endif
	KernelThread::switchToKernel();
	#ifndef BCC_BLOCK_IGNORE
		asm pop dx;
		asm pop cx;
	#endif
}

#endif /* __HELPSTRC_H_ */
