#include "SlepList.h"
#include "PCB.h"
#include "include.h"
#include "SCHEDULE.H"

SleepList::SleepList():head(0) {}

SleepList& SleepList::insert(PCB *pcb, Time timeToSleep) {
	if(timeToSleep <= 0)
		return *this;
	Elem* newElem = new Elem(pcb, timeToSleep);
	if(head == 0)
		head = newElem;
	else {
		Elem *curr = head, *prev = 0;
		while(curr->timeLeft<=newElem->timeLeft) {
			newElem->timeLeft -= curr->timeLeft;
			prev = curr;
			curr = curr->next;
			if(curr == 0)
				break;
		}

		if (prev == 0)
		{
			newElem->next = head;
			head = newElem;
		}
		else {
			prev->next = newElem;
			newElem->next = curr;
		}

		if(curr!=0)
			curr->timeLeft -= newElem->timeLeft;

	}
	return *this;

}

int SleepList::isEmpty() {
	return head == 0;
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
		if (head == 0)
			break;
	}
}

SleepList::~SleepList() {
	Elem *curr = head, *prev = 0;
	while(curr!=0)
	{
		prev = curr;
		curr = curr->next;
		delete prev;
	}
}

