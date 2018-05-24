#include "SlepList.h"
#include "PCB.h"
#include "include.h"
#include "SCHEDULE.H"

SleepList::SleepList():head(NULL) {}

SleepList& SleepList::insert(PCB *pcb, Time timeToSleep) {
	if(timeToSleep <= 0)
		return *this;
	Elem* newElem = new Elem(pcb, timeToSleep);
	if(head == NULL)
		head = newElem;
	else {
		Elem *curr = head, *prev = NULL;
		while(curr->timeLeft<=newElem->timeLeft) {
			newElem->timeLeft -= curr->timeLeft;
			prev = curr;
			curr = curr->next;
			if(curr == NULL)
				break;
		}

		if (prev == NULL)
		{
			newElem->next = head;
			head = newElem;
		}
		else {
			prev->next = newElem;
			newElem->next = curr;
		}

		if(curr!=NULL)
			curr->timeLeft -= newElem->timeLeft;

	}
	return *this;

}

int SleepList::isEmpty() {
	return head == NULL;
}

void SleepList::tick() {
	if(isEmpty())
		return;
	head->timeLeft--;
	while(head->timeLeft<=0)
	{
		head->pcb->setStatus(PCB::READY);
		Scheduler::put(head->pcb);
		Elem *temp = head;
		head = head->next;
		delete temp;
		if (head == NULL)
			break;
	}
}

SleepList::~SleepList() {
	// TODO Auto-generated destructor stub
}

