#include "BlckList.h"

BlockList::BlockList():head(NULL), tail(NULL) {}

BlockList::~BlockList() {
	if(isEmpty()) return;
	Elem *curr = head, *prev = NULL;
	while(curr!=NULL) {
		prev = curr;
		curr = curr->next;
		delete prev;
	}
	return;
}

int BlockList::isEmpty() {
	return head == NULL;
}

BlockList& BlockList::insert(PCB *pcb)
{
	lock;
	Elem* newElem(pcb);
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

PCB* BlockList::getAndRemove()
{
	if(isEmpty()) return NULL;

}
