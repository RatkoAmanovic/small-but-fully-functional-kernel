#ifndef __IVTENTRY_H_
#define __IVTENTRY_H_

#include "include.h"

class KernelEv;

#define PREPAREENTRY(numEntry, oldRoutine)\
Function interruptRoutine##numEntry; \
IVTEntry newIVTEntry##numEntry(numEntry, interruptRoutine##numEntry); \
void interrupt interruptRoutine##numEntry(...) {\
newIVTEntry##numEntry.signal();\
if (oldRoutine == 1)\
newIVTEntry##numEntry.oldRoutine();\
}

class IVTEntry {
	public:
		IVTEntry(IVTNo ivtNo, void interrupt (*newRoutine)(...));
		~IVTEntry();
		void signal();
		static IVTEntry *initIVTable();
	private:
		static IVTEntry *ivTable;
		IVTNo ivtNo;
		Function oldRoutine;
		KernelEv *event;
};

#endif /* __IVTENTRY_H_ */
