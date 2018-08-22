#include "IVTable.h"
#include "IVTEntry.h"
#include "Event.h"
#include <iostream.h>

IVTable::IVTable() {
	for (int i = 0; i < 256; ++i) {
		ivTable[i] = 0;
	}
}

IVTable::~IVTable() {
	delete [] ivTable;
	cout<<"IVT::Destructor"<<endl;
}

void IVTable::setEntry(IVTNo ivtNo, IVTEntry *ivtEntry) {
	ivTable[ivtNo] = ivtEntry;
}

IVTEntry* IVTable::getIVTEntry(IVTNo ivtNo) {
	return ivTable[ivtNo];
}
