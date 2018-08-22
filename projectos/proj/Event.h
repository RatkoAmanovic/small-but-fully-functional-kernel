#ifndef __EVENT_H_
#define __EVENT_H_

#include "include.h"
#include "IVTEntry.h"
#include "HelpStrc.h"

class KernelEv;


#define PREPAREENTRY(ivtNo, useOldRoutine)\
void interrupt interruptRoutine##ivtNo(...); \
IVTEntry newIVTEntry##ivtNo(ivtNo, interruptRoutine##ivtNo); \
void interrupt interruptRoutine##ivtNo(...) {\
newIVTEntry##ivtNo.signal();\
if (useOldRoutine == 1)\
newIVTEntry##ivtNo.runOldRoutine();\
};\

class Event {

	public:
		Event (IVTNo ivtNo);
		virtual ~Event ();
		void wait ();
		unsigned getId();
	protected:
		friend class KernelEv;
		void signal(); // can call KernelEv
	private:
		unsigned kernelEvId;
};
#endif //__EVENT_H_
