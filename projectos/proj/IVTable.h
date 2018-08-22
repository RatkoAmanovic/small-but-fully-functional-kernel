#ifndef __IVTABLE_H_
#define __IVTABLE_H_

#include "include.h"

class IVTEntry;

class IVTable {
	public:

		friend class KernelEv;
		friend class KernelThread;

		IVTable();
		~IVTable();
		void setEntry(IVTNo ivtNo, IVTEntry *ivtEntry);
		IVTEntry* getIVTEntry(IVTNo ivtNo);

		enum {TABLE_SIZE = 256};
		IVTEntry* ivTable[TABLE_SIZE];
	private:
};

#endif /* __IVTABLE_H_ */
