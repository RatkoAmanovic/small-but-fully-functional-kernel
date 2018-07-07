#include "KernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "CSwitch.h"
#include "EventLst.h"
#include "IVTEntry.h"
#include "IVTable.h"
#include "Event.h"
#include <dos.h>
#include "IdleThrd.h"

KernelEvList KernelEv::kernelEventList = KernelEvList();
unsigned KernelEv::ID = 0;

KernelEv::KernelEv(IVTNo ivtNo) : ivtNo(ivtNo), value(0) {
	myPCB = PCB::running;
	id = ID++;
	kernelEventList.insert(this);
	IVTEntry::ivTable->ivTable[ivtNo]->kernelEvent = this;
	IVTEntry::ivTable->getIVTEntry(ivtNo)->kernelEvent = this;
}

KernelEv::~KernelEv() {}

void KernelEv::wait() {
	lock;
	if(myPCB == PCB::running)
		if(value == 1)
			value--;
		else
			block();
	unlock;
}

void KernelEv::signal() {
	lock;
	if(value == 0) deblock();
	value = 1;
	unlock;
}

void KernelEv::block()
{
	lock;
	myPCB->setStatus(PCB::BLOCKED);
	KernelThread::threadDispatch();
	unlock;
}

void KernelEv::deblock()
{
	lock;
	myPCB->setStatus(PCB::READY);
	Scheduler::put(myPCB);
	unlock;
}

unsigned KernelEv::getId() {
	return id;
}
