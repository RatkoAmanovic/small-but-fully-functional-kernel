#ifndef __PCB_H_
#define __PCB_H_

#include <iostream.h>
#include <dos.h>
#include "include.h"
#include "BlckList.h"
#include "SlepList.h"
#include "IdleThrd.h"

class PCB
{
	public:

	char name;

		friend class Thread;
		friend class ContextSwitch;
		friend class KernelSem;
		friend class KernelEv;
		friend int main(int argc, char *argv[]);

		enum Status{
			NEW,RUNNING,READY,SLEEPING,BLOCKED,FINISHED
		};

		PCB(Thread *thread, StackSize stackSize, Time timeSlice, char n = ' ');
		~PCB();
		void setStatus(Status status);
		static PCB* getRuning();
		static int globalLock;

		 void start();
		 void waitToComplete();
		 static void sleep(Time timeToSleep);
		 static PCB* getPCBbyId(int id);
		 int getId();
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

		void initStack(StackSize stackSize);

		static void wrapper();//pokrece i zavrsava nit
};
#endif //__PCB_H_
