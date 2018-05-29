#ifndef __PCB_H_
#define __PCB_H_

#include <iostream.h>
#include <dos.h>
#include "include.h"
#include "BlckList.h"
#include "SlepList.h"
#include "IdleThrd.h"
#include "HelpStrc.h"

class PCB
{
	public:

		friend class Thread;
		friend class ContextSwitch;
		friend class KernelSem;
		friend class KernelEv;
		friend class KernelThread;
		friend int main(int argc, char *argv[]);

		enum Status{
			NEW,RUNNING,READY,SLEEPING,BLOCKED,FINISHED
		};

		PCB(Thread *thread, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
		PCB();
		~PCB();
		void setStatus(Status status);
		static PCB* getRuning();
		static int globalLock;

		 void start();
		 void waitToComplete();
		 static void sleep(Time timeToSleep);
		 static PCB* getPCBbyId(int id);
		 static void wrapper();
		 unsigned getId();
		 static int getIdleThreadId();

	private:
		static const StackSize MIN_PCB_STACK_SIZE;
		static const StackSize MAX_PCB_STACK_SIZE;

		static unsigned ID;
		unsigned id;

		static PCB *running;
		volatile Status status;

		BlockList blockedList;
		static SleepList sleepingList;
		static BlockList pcbList;

		volatile int localLock;

		unsigned *stack;
		volatile unsigned stackSegment;
		volatile unsigned stackPointer;
		volatile unsigned basePointer;
		Thread *thread;
		StackSize stackSize;
		Time timeSlice;
		int noTimer;

		void initKernelStack(StackSize stackSize);
		void initStack(StackSize stackSize);
};
#endif //__PCB_H_
