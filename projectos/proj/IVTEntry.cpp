#include "IVTEntry.h"
#include <dos.h>
#include "include.h"
#include "PCB.h"
#include "CSwitch.h"
#include "KernelEv.h"
#include "IVTable.h"

IVTable* IVTEntry::ivTable = new IVTable();

IVTEntry::IVTEntry(IVTNo ivtNo, InterruptFunction newRoutine) : ivtNo(ivtNo), kernelEvent(0) {
	cout<<"IVTE::Constructor"<<endl;
	lock;
	#ifndef BCC_BLOCK_IGNORE
		oldRoutine = getvect(ivtNo);
		setvect(ivtNo, newRoutine);
	#endif
		IVTEntry::ivTable->setEntry(ivtNo, this);
	unlock;
}

IVTEntry::~IVTEntry() {
	cout<<"IVTE::Destructor"<<endl;
	lock;
	IVTEntry::ivTable->setEntry(ivtNo, 0);
	restore();
	unlock;
}

void IVTEntry::signal() {
	lock;
	if(kernelEvent!=0) kernelEvent->signal();
	unlock;
}


void IVTEntry::runOldRoutine() {
	lock;
	if(oldRoutine != 0) (*oldRoutine)();
	unlock;
}

void IVTEntry::restore(){
lock;
#ifndef BCC_BLOCK_IGNORE
	if(oldRoutine != 0)
		setvect(ivtNo, oldRoutine);
	oldRoutine();
	oldRoutine = 0;
#endif
unlock;
}
