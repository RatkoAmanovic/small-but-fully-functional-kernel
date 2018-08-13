#include "Thread.h"
#include "PCB.h"
#include <dos.h>
#include <iostream.h>
#include "CSwitch.h"
#include "include.h"
#include <stdlib.h>
#include "SCHEDULE.H"
#include "HelpStrc.h"
#include "KernlThr.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock;
	Helper* helper = new Helper();
	helper->function = threadConstruct;
	helper->stackSize = stackSize;
	helper->timeSlice = timeSlice;
	#ifndef BCC_BLOCK_IGNORE
		helper->stackSegment = FP_SEG(this);
		helper->stackOffset = FP_OFF(this);
	#endif
	systemCall(helper);
	unlock;
	pcbId = helper->id;
	delete helper;
}

Thread::Thread(int i, int j, int k) {
}

Thread::~Thread() {
	waitToComplete();
	Helper* helper = new Helper();
	helper->function = threadDestruct;
	helper->id = pcbId;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

void Thread::start() {
	Helper* helper = new Helper();
	helper->function = threadStart;
	helper->id = pcbId;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

void Thread::waitToComplete() {
	Helper* helper = new Helper();
	helper->function = threadWaitToComplete;
	helper->id = pcbId;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

void Thread::sleep(Time timeToSleep) {
	Helper* helper = new Helper();
	helper->function = threadSleep;
	helper->timeSlice = timeToSleep;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

void Thread::resumeAll() {
	Helper* helper = new Helper();
	helper->function = threadResumeAll;
	helper->id = pcbId;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

void dispatch() {
	Helper* helper = new Helper();
	helper->function = threadDispatch;
	lock;
	systemCall(helper);
	unlock;
	delete helper;
}

unsigned Thread::getId() {
	return pcbId;
}

void Thread::wrapper(Thread* running) {
	running->run();
	running->resumeAll();
	dispatch();
}

