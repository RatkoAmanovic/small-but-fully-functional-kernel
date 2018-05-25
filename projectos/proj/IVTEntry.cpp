#include "IVTEntry.h"
#include <dos.h>
#include "include.h"
#include "PCB.h"
#include "CSwitch.h"
#include "KernelEv.h"

IVTEntry* IVTEntry::ivTable = IVTEntry::initIVTable();

IVTEntry::IVTEntry(IVTNo ivtNo, void interrupt (*newRoutine)(...)) : ivtNo(ivtNo), event(0) {
	lock;
	#ifndef BCC_BLOCK_IGNORE
		oldRoutine = getvect(ivtNo);
		setvect(ivtNo, newRoutine);
	#endif
	unlock;
}

IVTEntry::~IVTEntry() {
	lock;
	#ifndef BCC_BLOCK_IGNORE
		setvect(ivtNo, oldRoutine);
	#endif
	unlock;
}

void IVTEntry::signal() {
	lock;
	if(event!=0) event->signal();
	unlock;
}

IVTEntry* IVTEntry::initIVTable()
{
	IVTEntry *ivt[256];
	for (int i = 0; i < 256; ++i) {
		ivt[i] = 0;
	}
	return *ivt;
}

