#ifndef __HELPSTRC_H_
#define __HELPSTRC_H_

#include "include.h"

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



#endif /* __HELPSTRC_H_ */
