#ifndef __IVTABLE_H_
#define __IVTABLE_H_

#include "include.h"

class IVTEntry;

class IVTable {
	public:

		friend class Event;

		IVTable();
		~IVTable();
		void setEntry(IVTNo ivtNo, IVTEntry *ivtEntry);
		IVTEntry* getIVTEntry(IVTNo ivtNo);
	private:
		IVTEntry* ivTable[256];
};

#endif /* __IVTABLE_H_ */
