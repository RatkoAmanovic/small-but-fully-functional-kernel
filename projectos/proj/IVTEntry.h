#ifndef __IVTENTRY_H_
#define __IVTENTRY_H_

#include "include.h"

class KernelEv;
class IVTable;

class IVTEntry {
	public:

		friend class KernelEv;

		IVTEntry(IVTNo ivtNo, InterruptFunction newRoutine);
		~IVTEntry();
		void signal();
		void runOldRoutine();
		void restore();
	private:
		IVTNo ivtNo;
		InterruptFunction oldRoutine;
		KernelEv *kernelEvent;
		static IVTable* ivTable;
};

#endif /* __IVTENTRY_H_ */
