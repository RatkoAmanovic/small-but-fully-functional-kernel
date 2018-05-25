#include "BlckList.h"
#include "PCB.h"
#include "include.h"
#include "SCHEDULE.H"
#include "CSwitch.h"
#include <iostream.h>

BlockList::BlockList():head(0), tail(0) {}

BlockList::~BlockList() {
	resumeAll();
}

int BlockList::isEmpty() {
	return head == 0;
}

BlockList& BlockList::insert(PCB *pcb)
{
	lock;
	Elem* newElem = new Elem(pcb);
	if(head == 0) {
		head = newElem;
		tail = head;
	}
	else {
		tail->next = newElem;
		tail = tail->next;
	}
	unlock;
	return *this;
}

void BlockList::resumeAll(){
	if(isEmpty()) return;
	Elem *curr = head, *prev = 0;
	while(curr!=0) {
		curr->pcb->setStatus(PCB::READY);
		Scheduler::put(curr->pcb);
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	curr = 0;
	prev = 0;
	head = 0;
	tail = 0;
	return;
}

PCB* BlockList::getFirst()
{
	if(isEmpty()) return 0;
	PCB *pcb = head->pcb;
	if(head->next==0)
	{
		delete head;
		head = 0;
	}
	else
	{
		Elem *temp = head;
		head = head->next;
		delete temp;
	}
	return pcb;
}
