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
	cout<<"T::Constructor"<<endl;
	Helper* helper = new Helper();
	helper->function = threadConstruct;
	helper->stackSize = stackSize;
	helper->timeSlice = timeSlice;
	#ifndef BCC_BLOCK_IGNORE
		CONSTRUCTOR_SYSTEM_CALL;
	#endif

	pcbId = helper->id;
	unlock;
	delete helper;
}

Thread::Thread(int i, int j, int k) {
}

Thread::~Thread() {
	Helper* helper = new Helper();
	helper->function = threadDestruct;
	helper->id = pcbId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

void Thread::start() {
	Helper* helper = new Helper();
	helper->function = threadStart;
	helper->id = pcbId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

void Thread::waitToComplete() {
	Helper* helper = new Helper();
	helper->function = threadWaitToComplete;
	helper->id = pcbId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

void Thread::sleep(Time timeToSleep) {
	Helper* helper = new Helper();
	helper->function = threadDestruct;
	helper->timeSlice = timeToSleep;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

void Thread::resumeAll() {
	Helper* helper = new Helper();
	helper->function = threadWaitToComplete;
	helper->id = pcbId;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
	delete helper;
}

void dispatch() {
	Helper* helper = new Helper();
	helper->function = threadDispatch;
	#ifndef BCC_BLOCK_IGNORE
		SYSTEM_CALL;
	#endif
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
