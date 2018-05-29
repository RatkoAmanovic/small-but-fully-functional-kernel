#include "Event.h"
#include "KernelEv.h"
#include "PCB.h"
#include <dos.h>
#include <iostream.h>
#include "include.h"
#include "CSwitch.h"
#include "IVTEntry.h"
#include "IVTable.h"
#include "HelpStrc.h"
#include "KernlThr.h"

Event::Event(IVTNo ivtNo) {
	Helper* helper = new Helper();
	helper->function = eventConstruct;
	helper->ivtNo = ivtNo;
	#ifndef BCC_BLOCK_IGNORE
		helper->stackSegment = FP_SEG(this);
		helper->stackOffset = FP_OFF(this);

		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	kernelEvId = helper->id;
	delete helper;
}

Event::~Event() {
	Helper* helper = new Helper();
	helper->function = eventDestruct;
	helper->id = kernelEvId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	delete helper;
}

void Event::wait() {
	Helper* helper = new Helper();
	helper->function = eventWait;
	helper->id = kernelEvId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	delete helper;
}

void Event::signal() {
	Helper* helper = new Helper();
	helper->function = eventSignal;
	helper->id = kernelEvId;
	#ifndef BCC_BLOCK_IGNORE
		unsigned helperSegment = FP_SEG(helper);
		unsigned helperOffset = FP_OFF(helper);

		asm mov cx, helperSegment;
		asm mov dx, helperOffset;
	#endif
	KernelThread::switchDomain();
	delete helper;
}



