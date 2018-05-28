#include "IVTable.h"
#include "IVTEntry.h"
#include "Event.h"
IVTable::IVTable() {
	for (int i = 0; i < 256; ++i) {
		ivTable[i] = 0;
	}
}

IVTable::~IVTable() {
	// TODO Auto-generated destructor stub
}

void IVTable::setEntry(IVTNo ivtNo, IVTEntry *ivtEntry) {
	ivTable[ivtNo] = ivtEntry;
}

IVTEntry* IVTable::getIVTEntry(IVTNo ivtNo) {
	return ivTable[ivtNo];
}
