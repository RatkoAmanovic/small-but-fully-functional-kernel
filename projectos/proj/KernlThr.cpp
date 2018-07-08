#include "KernlThr.h"
#include "HelpStrc.h"
#include "CSwitch.h"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "IdleThrd.h"
#include "Thread.h"
#include "include.h"
#include "Event.h"
#include "KernelEv.h"
#include "KernlSem.h"
#include "Semaphor.h"


volatile int KernelThread::kernelThreadRequestedSwitch = 0;
KernelThread* KernelThread::kernelThread = 0;
volatile Helper* KernelThread::helper = 0;
volatile PCB* KernelThread::myPCB = 0;
volatile Function* KernelThread::functions = 0;
const int KernelThread::SWITCH_TO_KERNEL_ENTRY = 0x60;
const int KernelThread::SWITCH_TO_USER_ENTRY = 0x61;

volatile unsigned tempStackSegmentKT = 0;
volatile unsigned tempStackPointerKT = 0;
volatile unsigned tempBasePointerKT = 0;
volatile unsigned tempCX = 0;
volatile unsigned tempDX = 0;

KernelThread::KernelThread() {

	functions = new Function[16];
	functions[0] = KernelThread::threadConstruct;
	functions[1] = KernelThread::threadStart;
	functions[2] = KernelThread::threadWaitToComplete;
	functions[3] = KernelThread::threadSleep;
	functions[4] = KernelThread::threadDispatch;
	functions[5] = KernelThread::threadResumeAll;
	functions[6] = KernelThread::threadDestruct;
	functions[7] = KernelThread::eventConstruct;
	functions[8] = KernelThread::eventWait;
	functions[9] = KernelThread::eventSignal;
	functions[10] = KernelThread::eventDestruct;
	functions[11] = KernelThread::semaphoreConstruct;
	functions[12] = KernelThread::semaphoreWait;
	functions[13] = KernelThread::semaphoreSignal;
	functions[14] = KernelThread::semaphoreValue;
	functions[15] = KernelThread::semaphoreDestruct;
}

KernelThread::~KernelThread() {}

KernelThread* KernelThread::getKernelThread() {
	if (kernelThread == 0) {
		kernelThread = new KernelThread();
		myPCB = new PCB();
	}
	return kernelThread;
}

void KernelThread::run() {
	while(1) {
		functions[helper->function]();
		KernelThread::switchToUser();
	}
}

void interrupt KernelThread::switchToKernel(...) {

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tempStackSegmentKT, ss
			mov tempStackPointerKT, sp
			mov tempBasePointerKT, bp
		}
	#endif
	PCB::running->stackSegment = tempStackSegmentKT;
	PCB::running->stackPointer = tempStackPointerKT;
	PCB::running->basePointer = tempBasePointerKT;
	PCB::running->localLock = PCB::globalLock;

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tempCX, cx
			mov tempDX, dx
		}
		helper = (Helper*)MK_FP(tempCX, tempDX);
	#endif

	tempStackSegmentKT = myPCB->stackSegment;
	tempStackPointerKT = myPCB->stackPointer;
	tempBasePointerKT = myPCB->basePointer;
	PCB::globalLock = myPCB->localLock;

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov ss, tempStackSegmentKT
			mov sp, tempStackPointerKT
			mov bp, tempBasePointerKT
		}
	#endif
}

void interrupt KernelThread::switchToUser(...) {
	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tempStackSegmentKT, ss
			mov tempStackPointerKT, sp
			mov tempBasePointerKT, bp
		}
	#endif

	myPCB->stackSegment = tempStackSegmentKT;
	myPCB->stackPointer = tempStackPointerKT;
	myPCB->basePointer = tempBasePointerKT;

	myPCB->localLock = PCB::globalLock;

	if(kernelThreadRequestedSwitch == 1) {
		if(PCB::running->status == PCB::RUNNING && PCB::running->thread != IdleThread::getIdleThread()) {
			PCB::running->setStatus(PCB::READY);
			Scheduler::put(PCB::running);
		}

		PCB::running = Scheduler::get();

		if(PCB::running == 0)
			PCB::running = PCB::getPCBbyId(PCB::getIdleThreadId());
		PCB::running->setStatus(PCB::RUNNING);
		ContextSwitch::counter = PCB::running->timeSlice;
	}
	PCB::globalLock = PCB::running->localLock;

	tempStackSegmentKT = PCB::running->stackSegment;
	tempStackPointerKT = PCB::running->stackPointer;
	tempBasePointerKT = PCB::running->basePointer;

	ContextSwitch::counter = PCB::running->timeSlice;

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov ss, tempStackSegmentKT
			mov sp, tempStackPointerKT
			mov bp, tempBasePointerKT
		}
	#endif
	kernelThreadRequestedSwitch = 0;
}

void KernelThread::threadConstruct() {
//	cout<<"KT::threadConst "<<PCB::ID<<endl;
	Thread* thread = 0;

	#ifndef BCC_BLOCK_IGNORE
		thread = (Thread*)MK_FP(helper->stackSegment, helper->stackOffset);
	#endif
	lock;
	new PCB(thread, helper->timeSlice, helper->stackSize);
	unlock;
	helper->id = PCB::ID - 1; //when inserting pcb his id will be id = ID++;
}

void KernelThread::threadDestruct() {
//	cout<<"KT::threadDestruct "<<helper->id<<endl;
	PCB::pcbList.removeById(helper->id);
}

void KernelThread::threadStart() {
//	cout<<"KT::threadStart "<<helper->id<<endl;

	PCB* myPCB = PCB::pcbList.getById(helper->id);
	myPCB->setStatus(PCB::READY);
	Scheduler::put(myPCB);
}

void KernelThread::threadWaitToComplete() {
//	cout<<"KT::threadWaitToComplete "<<helper->id<<endl;
	PCB::pcbList.getById(helper->id)->waitToComplete();
}

void KernelThread::threadSleep() {
//	cout<<"KT::threadSleep "<<helper->timeSlice<<endl;
	PCB::running->sleep(helper->timeSlice);
}

void KernelThread::threadDispatch() {
//	cout<<"KT::threadDispatch "<<endl;
	kernelThreadRequestedSwitch = 1;
}

void KernelThread::threadResumeAll() {
//	cout<<"KT::threadResumeAll "<<PCB::running->getId()<<endl;
	PCB::running->setStatus(PCB::FINISHED);
	PCB::pcbList.getById(helper->id)->blockedList.resumeAll();
}

void KernelThread::eventConstruct() {
//	cout<<"KT::eventConst"<<endl<<endl<<endl;

	lock;
	new KernelEv(helper->ivtNo);
	unlock;
	helper->id = KernelEv::ID - 1;
}

void KernelThread::eventDestruct() {
//	cout<<"KT::eventDest"<<endl<<endl<<endl;

	KernelEv::kernelEventList.removeById(helper->id);
}

void KernelThread::eventWait() {
//	cout<<"KT::eventWait"<<endl<<endl<<endl;

	KernelEv::kernelEventList.getById(helper->id)->wait();
}

void KernelThread::eventSignal() {
//	cout<<"KT::eventSignal"<<endl<<endl<<endl;

	KernelEv::kernelEventList.getById(helper->id)->signal();
}

void KernelThread::semaphoreConstruct() {
//	cout<<"KT::semaphoreConst"<<endl<<endl;

	lock;
	new KernelSem(helper->init);
	unlock;
	helper->id = KernelSem::ID - 1;
}

void KernelThread::semaphoreDestruct() {
//	cout<<"KT::semaphoreDest"<<endl<<endl;
	KernelSem::kernelSemaphoreList.removeById(helper->id);
}

void KernelThread::semaphoreWait() {
//	cout<<"KT::semaphoreWait"<<endl<<endl;

	int temp = 0;
	temp = KernelSem::kernelSemaphoreList.getById(helper->id)->wait();
	helper->init = temp;
}

void KernelThread::semaphoreValue() {
//	cout<<"KT::semaphoreVal "<<helper->id<<endl<<endl;

	int temp = 0;
	temp = KernelSem::kernelSemaphoreList.getById(helper->id)->val();
	helper->init = temp;
}

void KernelThread::semaphoreSignal() {
//	cout<<"KT::semaphoreSingal"<<endl<<endl;

	KernelSem::kernelSemaphoreList.getById(helper->id)->signal();
}

void KernelThread::inic() {
#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	setvect(SWITCH_TO_KERNEL_ENTRY, switchToKernel);
	setvect(SWITCH_TO_USER_ENTRY, switchToUser);
	asm popf;
#endif
}
