#include "Event.h"
#include "KernelEv.h"
#include "PCB.h"
#include "CSwitch.h"
#include "IVTEntry.h"
#include "IVTable.h"
Event::Event(IVTNo ivtNo) {
	lock;
	myImpl = new KernelEv(ivtNo);
	IVTEntry::ivTable->ivTable[ivtNo]->event = this;
	//IVTEntry::ivTable->getIVTEntry(ivtNo)->event = this;
	unlock;
}

Event::~Event() {
	lock;
	delete myImpl;
	unlock;
}

void Event::wait() {
	lock;
	myImpl->wait();
	unlock;
}

void Event::signal() {
	lock;
	myImpl->signal();
	unlock;
}

