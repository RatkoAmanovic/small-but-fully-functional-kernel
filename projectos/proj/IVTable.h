#ifndef __IVTABLE_H_
#define __IVTABLE_H_

#include "include.h"

class IVTEntry;

class IVTable {
	public:

		friend class KernelEv;

		IVTable();
		~IVTable();
		void setEntry(IVTNo ivtNo, IVTEntry *ivtEntry);
		IVTEntry* getIVTEntry(IVTNo ivtNo);
	private:
		enum {TABLE_SIZE = 256};
		IVTEntry* ivTable[TABLE_SIZE];
};

#endif /* __IVTABLE_H_ */
