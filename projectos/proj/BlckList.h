#ifndef __BLCKLIST_H_
#define __BLCKLIST_H_

#include <iostream.h>

class PCB;

class BlockList {
	public:
		BlockList();
		~BlockList();
		BlockList& insert(PCB *pcb);
		void resumeAll();
		int isEmpty();
		PCB* getFirst();
	private:
		typedef struct Elem{
			PCB *pcb;
			Elem *next;
			Elem(PCB *pcb) : pcb(pcb), next(NULL) {};
		};
		Elem *head, *tail;
};

#endif /* __BLCKLIST_H_ */
