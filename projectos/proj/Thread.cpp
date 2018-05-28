#include "Thread.h"
#include "PCB.h"
#include <dos.h>
#include <iostream.h>
#include "CSwitch.h"
#include "include.h"
#include <stdlib.h>
#include "SCHEDULE.H"

Thread::Thread(StackSize stackSize, Time timeSlice, char n) {

	myPCB = new PCB(this, stackSize, timeSlice, n);
}

Thread::~Thread() {
	delete myPCB;
}

void Thread::start() {
	lock;
	myPCB->setStatus(PCB::READY);
	Scheduler::put(myPCB);
	unlock;
}

void Thread::waitToComplete() {
	myPCB->waitToComplete();
}

void Thread::sleep(Time timeToSleep) {
	PCB::sleep(timeToSleep);
}

void dispatch() {
	#ifndef BCC_BLOCK_IGNORE
		asm pushf;
		asm cli;
		ContextSwitch::requestSwitch();
		ContextSwitch::timer();
		asm popf;
	#endif
}

int Thread::getId() {
	return myPCB->getId();
}
