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
	cout<<"KS::Wait"<<endl;
	int temp;
	value--;
	if(value<0) {
		temp = 1;
		block();
	}
	else
		temp = 0;
	cout<<"KS::Wait::temp = "<<temp<<endl;
	return temp;
}

void KernelSem::signal() {
	cout<<"KS::Signal"<<endl;
	if(value++ < 0)
		deblock();
}

int KernelSem::val() const {
	cout<<"KS::Val"<<endl;
	return value;
}

void KernelSem::block() {
	PCB::running->setStatus(PCB::BLOCKED);
	blockedList.insert(PCB::running);
	KernelThread::threadDispatch();
}

void KernelSem::deblock() {
	PCB *pcb = blockedList.takeFirst();
	if(pcb!=0) {
		pcb->setStatus(PCB::READY);
		Scheduler::put(pcb);
	}
}

unsigned KernelSem::getId(){
	return id;
}
