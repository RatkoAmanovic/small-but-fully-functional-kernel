#ifndef __PCB_H_
#define __PCB_H_

#include <iostream.h>
#include <dos.h>
#include "include.h"

class PCB
{
public:

	friend Thread;

	enum Status{
		NEW,RUNNING,READY,BLOCKED,FINISHED
	};

	PCB(Thread *thread, StackSize stackSize, Time timeSlice);
	~PCB();
	void setStatus(Status status);
	static PCB* getRuning();
	static int globalLock;

private:
	static const StackSize MIN_PCB_STACK_SIZE;
	static const StackSize MAX_PCB_STACK_SIZE;

	static unsigned ID;
	unsigned id;
	static PCB *running;


	volatile int localLock;

	unsigned *stack;
	volatile unsigned stackSegment;
	volatile unsigned stackPointer;
	volatile unsigned basePointer;
	volatile Status status;
	Thread *thread;
	StackSize stackSize;
	Time timeSlice;



	void initStack(StackSize stackSize);

	static void wrapper();//pokrece nit
};
#endif //__PCB_H_
