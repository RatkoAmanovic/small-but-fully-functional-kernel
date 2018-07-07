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
	systemCall(helper);
	kernelEvId = helper->id;
	delete helper;
}

Event::~Event() {
	Helper* helper = new Helper();
	helper->function = eventDestruct;
	helper->id = kernelEvId;
	systemCall(helper);
	delete helper;
}

void Event::wait() {
	Helper* helper = new Helper();
	helper->function = eventWait;
	helper->id = kernelEvId;
	systemCall(helper);
	delete helper;
}

void Event::signal() {
	Helper* helper = new Helper();
	helper->function = eventSignal;
	helper->id = kernelEvId;
	systemCall(helper);
	delete helper;
}


