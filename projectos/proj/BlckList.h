#ifndef __BLCKLIST_H_
#define __BLCKLIST_H_

#include "include.h"
#include <iostream.h>

class BlockList {
	public:
		BlockList();
		~BlockList();
		BlockList& insert(PCB *pcb);
		PCB* getAndRemove();
		int isEmpty();
	private:
		typedef struct Elem{
			PCB *pcb;
			Elem *next;
			Elem(PCB *pcb) : pcb(pcb), next(NULL) {};
		};
		Elem *head, *tail;
};

#endif /* __BLCKLIST_H_ */
