#include "SemapLst.h"
#include "KernlSem.h"
#include "include.h"
#include "SCHEDULE.H"
#include "CSwitch.h"
#include <iostream.h>
#include "Semaphor.h"
#include "PCB.h"

KernelSemList::KernelSemList():head(0), tail(0) {}

KernelSemList::~KernelSemList() {
	resumeAll();
}

int KernelSemList::isEmpty() {
	return head == 0;
}

KernelSemList& KernelSemList::insert(KernelSem *semaphore)
{
	Elem* newElem = new Elem(semaphore);
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

void KernelSemList::resumeAll(){
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

KernelSem* KernelSemList::takeFirst()
{
	if(isEmpty()) return 0;
	KernelSem *semaphore = head->semaphore;
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
	return semaphore;
}

KernelSem* KernelSemList::getById(int id) {
	if(isEmpty()) return 0;
	Elem *curr = head;
	KernelSem *semaphore = 0;
	while(curr!=0)
	{
		if(id==curr->semaphore->getId())
		{
			semaphore = curr->semaphore;
			break;
		}
		curr = curr->next;
	}
	return semaphore;
}

void KernelSemList::removeById(int id) {
	if(isEmpty()) return;
		Elem *curr = head, *prev = 0;
		while(curr!=0)
		{
			if(id==curr->semaphore->getId())
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
