#include "KernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "CSwitch.h"

KernelEv::KernelEv(IVTNo ivtNo) : ivtNo(ivtNo), value(0) {
	myPCB = PCB::running;
}

KernelEv::~KernelEv() {
	// TODO Auto-generated destructor stub
}

void KernelEv::wait() {
	lock;
	if(myPCB == PCB::running)
		if(value == 1)
			value--;
		else
			block();
	unlock;
}

void KernelEv::signal()
{
	lock;
	if(value == 0) deblock();
	value = 1;
	unlock;
}

void KernelEv::block()
{
	lock;
	myPCB->setStatus(PCB::BLOCKED);
	dispatch();
	unlock;
}

void KernelEv::deblock()
{
	lock;
	myPCB->setStatus(PCB::READY);
	Scheduler::put(myPCB);
	unlock;
}
