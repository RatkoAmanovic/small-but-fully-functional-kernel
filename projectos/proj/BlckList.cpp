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

BlockList& BlockList::insert(PCB *pcb) {
	Elem* newElem = new Elem(pcb);

	if(head == 0) {
		head = newElem;
		tail = head;
	}
	else {
		tail->next = newElem;
		tail = tail->next;
	}
	return *this;
}

void BlockList::resumeAll() {
	if(isEmpty())
		return;

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

PCB* BlockList::takeFirst() {
	if(isEmpty())
		return 0;

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

PCB* BlockList::getById(int id) {
	if(isEmpty())
		return 0;

	Elem *curr = head;
	PCB *pcb = 0;
	while(curr!=0)
	{
		if(id==curr->pcb->getId())
		{
			pcb = curr->pcb;
			break;
		}
		curr = curr->next;
	}
	return pcb;
}

void BlockList::removeById(int id) {
	if(isEmpty())
		return;

	Elem *curr = head, *prev = 0;
	while(curr!=0)
	{
		if(id==curr->pcb->getId())
		{
			if(prev==0) {
				takeFirst();
			}
			else {
				if(curr!=0) {
					if(curr == tail)
						tail = prev;
					prev->next = curr->next;
					delete curr;
				}
			}
			break;
		}
		prev = curr;
		curr = curr->next;
	}
}
