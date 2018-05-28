#include "PCB.h"
#include <dos.h>
#include "Thread.h"
#include "BlckList.h"
#include "SlepList.h"
#include "CSwitch.h"
#include "IdleThrd.h"

unsigned PCB::ID = 0;
const StackSize PCB::MIN_PCB_STACK_SIZE = 0x400;
const StackSize PCB::MAX_PCB_STACK_SIZE = 0x1000;
PCB* PCB::running = NULL;
int PCB::globalLock = 0;
SleepList PCB::sleepingList = SleepList();
BlockList PCB::pcbList = BlockList();

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice, char n) : thread(thread),stackSize(stackSize),timeSlice(timeSlice){
	name = n;
	id = ID++;
	localLock = 0;
	initStack(stackSize);
	pcbList.insert(this);
}

void PCB::initStack(StackSize stackSize)
{
	if(stackSize>MAX_PCB_STACK_SIZE) this->stackSize = MAX_PCB_STACK_SIZE;
	if(stackSize<MIN_PCB_STACK_SIZE) this->stackSize = MIN_PCB_STACK_SIZE;

	this->stackSize /= sizeof(unsigned);
	stackSize = this->stackSize;

	stack = new unsigned[stackSize];

	#ifndef BCC_BLOCK_IGNORE

	//PSW I = 1
	stack[stackSize - 1] = 0x200;
	//Wrapper
	stack[stackSize - 2] = FP_SEG(PCB::wrapper);
	stack[stackSize - 3] = FP_OFF(PCB::wrapper);
	//Base Pointer
	stack[stackSize - 12] = 0;

	stackSegment = FP_SEG(stack + stackSize - 12);
	stackPointer = FP_OFF(stack + stackSize - 12);
	basePointer = stackPointer;

	#endif
}

PCB::~PCB()
{
	delete[] stack;
}

void PCB::setStatus(Status status) {
	this->status = status;
}

PCB* PCB::getRuning() {
	return running;
}

void PCB::wrapper() {
	running->thread->run();
	lock;
	running->setStatus(PCB::FINISHED);
	running->blockedList.resumeAll();
	dispatch();
}

void PCB::waitToComplete() {
	lock;
	if(running == this || status==PCB::FINISHED || running->thread == IdleThread::getIdleThread())//TODO: add idle thread
	{
		unlock;
		return;
	}
	running->setStatus(PCB::BLOCKED);
	blockedList.insert(running);
	dispatch();
	unlock;
}

void PCB::sleep(Time timeToSleep) {
	lock;
	if(timeToSleep <= 0)
		return;
	running->setStatus(PCB::SLEEPING);
	sleepingList.insert(running, timeToSleep);
	dispatch();
	unlock;
}

PCB* PCB::getPCBbyId(int id) {
	return PCB::pcbList.getById(id);
}

int PCB::getId() {
	return id;
}

int PCB::getIdleThreadId() {
	return IdleThread::idleThread->getId();
}
