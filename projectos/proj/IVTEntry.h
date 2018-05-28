#ifndef __IVTENTRY_H_
#define __IVTENTRY_H_

#include "include.h"

class KernelEv;
class IVTable;
class Event;
class IVTEntry {
	public:

		friend class Event;

		IVTEntry(IVTNo ivtNo, void interrupt (*newRoutine)(...));
		~IVTEntry();
		void signal();
		void runOldRoutine();
	private:
		IVTNo ivtNo;
		Function oldRoutine;
		Event *event;
		static IVTable* ivTable;
};

#endif /* __IVTENTRY_H_ */
