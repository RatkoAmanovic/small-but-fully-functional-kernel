#include "BlckList.h"

BlockList::BlockList():head(NULL), tail(NULL) {}

BlockList::~BlockList() {
	resumeAll();
}

int BlockList::isEmpty() {
	return head == NULL;
}

BlockList& BlockList::insert(PCB *pcb)
{
	lock;
	Elem* newElem = new Elem(pcb);
	if(head == NULL) {
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
	Elem *curr = head, *prev = NULL;
	while(curr!=NULL) {
		curr->pcb->setStatus(PCB::READY);
		Scheduler::put(curr->pcb);
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	curr = NULL;
	prev = NULL;
	head = NULL;
	tail = NULL;
	return;
}
