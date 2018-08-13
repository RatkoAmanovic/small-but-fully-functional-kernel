#include "PCB.h"
#include <dos.h>
#include "Thread.h"
#include "BlckList.h"
#include "SlepList.h"
#include "CSwitch.h"
#include "IdleThrd.h"
#include "KernlThr.h"

unsigned PCB::ID = 0;
const StackSize PCB::MIN_PCB_STACK_SIZE = 0x400;
const StackSize PCB::MAX_PCB_STACK_SIZE = 0x1000;
PCB* PCB::running = 0;
int PCB::globalLock = 0;
SleepList PCB::sleepingList = SleepList();
BlockList PCB::pcbList = BlockList();

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice) : thread(thread),stackSize(stackSize),timeSlice(timeSlice) {
////	cout<<"Created PCB with id"<<ID<<endl;
//	if(stackSize==0){
////		cout<<"Created IdlePCB "<<ID<<endl;
//	}
	id = ID++;
	localLock = 0;
	if(timeSlice==0)
		noTimer = 1;
	else
		noTimer = 0;
	initStack(stackSize);
	pcbList.insert(this);
}

PCB::PCB() {
	cout<<"PCB::kernelConst"<<endl;
	id = ID++;
	localLock = 1;
	timeSlice = defaultTimeSlice;
	stackSize = defaultStackSize;
	initKernelStack(stackSize);
}

void PCB::initStack(StackSize stackSize) {
	if(stackSize>MAX_PCB_STACK_SIZE) this->stackSize = MAX_PCB_STACK_SIZE;
	if(stackSize<MIN_PCB_STACK_SIZE) this->stackSize = MIN_PCB_STACK_SIZE;

	this->stackSize /= sizeof(unsigned);
	stackSize = this->stackSize;

	stack = new unsigned[stackSize];

	#ifndef BCC_BLOCK_IGNORE
		stack[stackSize - 1] = FP_SEG(thread);
		stack[stackSize - 2] = FP_OFF(thread);

		stack[stackSize - 5] = 0x200;

		stack[stackSize - 6] = FP_SEG(Thread::wrapper);
		stack[stackSize - 7] = FP_OFF(Thread::wrapper);

		stack[stackSize - 16] = 0;

		stackSegment = FP_SEG(stack + stackSize - 16);
		stackPointer = FP_OFF(stack + stackSize - 16);
		basePointer = stackPointer;
	#endif
}

void PCB::initKernelStack(StackSize stackSize) {
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

PCB::~PCB() {
	delete[] stack;
}

void PCB::setStatus(Status status) {
	this->status = status;
}

PCB* PCB::getRuning() {
	return running;
}

void PCB::waitToComplete() {
//	if(status!=FINISHED)
//	cout<<"PCB::waitToComplete "<<endl;
//	cout<<"PCB::waitToComplete "<<running->id<<endl<<id<<endl;
	if(running != this && status!=FINISHED && running->thread->getId()!=PCB::getIdleThreadId()) {
//	if(running != this && status!=PCB::FINISHED) {

//	if(status!=PCB::FINISHED){
//		cout<<"PCB::waitToComplete::Uslo"<<endl;
		running->setStatus(PCB::BLOCKED);
		blockedList.insert(running);
		KernelThread::threadDispatch();
	}
}

void PCB::sleep(Time timeToSleep) {
	if(timeToSleep <= 0)
		return;
	running->setStatus(PCB::SLEEPING);
	sleepingList.insert(running, timeToSleep);
	KernelThread::threadDispatch();
}

PCB* PCB::getPCBbyId(int id) {
	return PCB::pcbList.getById(id);
}

unsigned PCB::getId() {
	return id;
}

int PCB::getIdleThreadId() {
	return 1;
}

void PCB::wrapper() {
	KernelThread::run();
}
