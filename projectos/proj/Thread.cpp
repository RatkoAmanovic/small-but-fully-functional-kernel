#include "Thread.h"
#include "PCB.h"
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

