#include "PCB.h"
#include <dos.h>
#include "Thread.h"

unsigned PCB::ID = 0;
const StackSize PCB::MIN_PCB_STACK_SIZE = 0x400;
const StackSize PCB::MAX_PCB_STACK_SIZE = 0x1000;
PCB* PCB::running = NULL;
int PCB::globalLock = 0;

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice) : thread(thread),stackSize(stackSize),timeSlice(timeSlice){
	id = ID++;
	lock = 0;
	initStack(stackSize);
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

void PCB::setStatus(Status status)
{
	this->status = status;
}

PCB* PCB::getRuning()
{
	return running;
}
