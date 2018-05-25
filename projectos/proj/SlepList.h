#ifndef __SLEPLIST_H_
#define __SLEPLIST_H_

#include <iostream.h>
#include "include.h"

class PCB;

class SleepList {
	public:
		SleepList();
		~SleepList();
		SleepList& insert(PCB *pcb, Time timeToSleep);
		int isEmpty();
		void tick();
	private:
		typedef struct Elem{
			Time timeLeft;
			PCB *pcb;
			Elem *next;
			Elem(PCB *pcb, Time timeToSleep) : pcb(pcb), timeLeft(timeToSleep), next(0) {}
		};
		Elem *head;
};

#endif /* __SLEPLIST_H_ */
