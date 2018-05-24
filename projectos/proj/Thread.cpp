#include "Thread.h"
#include "PCB.h"
#include <dos.h>
#include <iostream.h>
#include "CSwitch.h"
#include "include.h"
#include <stdlib.h>
#include "SCHEDULE.H"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	myPCB = new PCB(this, stackSize, timeSlice);
}

Thread::~Thread() {
	// TODO Auto-generated destructor stub
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
	asm cli;
	ContextSwitch::requestSwitch();
	//timer();TODO
	asm sti;
//	asm pushf;
//	asm cli;
//	ContextSwitch::requestSwitch();
//	//TODO:timer
//	asm popf;
}
