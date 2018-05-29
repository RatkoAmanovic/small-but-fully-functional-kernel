#include "EventLst.h"
#include "KernelEv.h"
#include "include.h"
#include "SCHEDULE.H"
#include "CSwitch.h"
#include <iostream.h>
#include "PCB.h"

KernelEvList::KernelEvList():head(0), tail(0) {}

KernelEvList::~KernelEvList() {
	resumeAll();
}

int KernelEvList::isEmpty() {
	return head == 0;
}

KernelEvList& KernelEvList::insert(KernelEv *event)
{
	lock;
	Elem* newElem = new Elem(event);
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

void KernelEvList::resumeAll(){
	if(isEmpty()) return;
	Elem *curr = head, *prev = 0;
	while(curr!=0) {
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

KernelEv* KernelEvList::takeFirst()
{
	if(isEmpty()) return 0;
	KernelEv *event = head->event;
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
	return event;
}

KernelEv* KernelEvList::getById(int id) {
	if(isEmpty()) return 0;
	Elem *curr = head;
	KernelEv *event = 0;
	while(curr!=0)
	{
		if(id==curr->event->getId())
		{
			event = curr->event;
			break;
		}
		curr = curr->next;
	}
	return event;
}

void KernelEvList::removeById(int id) {
	if(isEmpty()) return;
		Elem *curr = head, *prev = 0;
		while(curr!=0)
		{
			if(id==curr->event->getId())
			{
				if(prev==0) {
					takeFirst();
				}
				else {
					if(curr!=0) {
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
