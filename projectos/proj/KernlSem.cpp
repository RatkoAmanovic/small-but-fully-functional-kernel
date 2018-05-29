#include "KernlSem.h"
#include "include.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Thread.h"
#include "CSwitch.h"
#include "KernlThr.h"
#include "Semaphor.h"
#include "SemapLst.h"

KernelSemList KernelSem::kernelSemaphoreList = KernelSemList();
unsigned KernelSem::ID = 0;

KernelSem::KernelSem(int init) : value(init) {
	id = ID++;
	kernelSemaphoreList.insert(this);
}

KernelSem::~KernelSem() {
	PCB *pcb = blockedList.takeFirst();
	while(pcb!=0)
		pcb = blockedList.takeFirst();
	delete pcb;
}

int KernelSem::wait() {
	int temp;
	lock;
	value--;
	if(value<0) {
		block();
		temp = 1;
	}
	else
		temp = 0;
	unlock;
	return temp;
}

void KernelSem::signal() {
	lock;
	if(value++ < 0)
		deblock();
	unlock;
}

int KernelSem::val() const {
	return value;
}

void KernelSem::block() {
	lock;
	PCB::running->setStatus(PCB::BLOCKED);
	blockedList.insert(PCB::running);
	dispatch();
	unlock;
}

void KernelSem::deblock() {
	lock;
	PCB *pcb = blockedList.takeFirst();
	if(pcb!=0) {
		pcb->setStatus(PCB::READY);
		Scheduler::put(pcb);
	}
	unlock;
}

unsigned KernelSem::getId(){
	return id;
}
