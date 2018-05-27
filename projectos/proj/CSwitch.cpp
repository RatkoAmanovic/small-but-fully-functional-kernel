#include "CSwitch.h"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "IdleThrd.h"
#include "Thread.h"

volatile int ContextSwitch::switchRequested = 0;
volatile Time ContextSwitch::counter = 0;
Function ContextSwitch::oldTimer = 0;
volatile int ContextSwitch::timePassed = 0;

const int ContextSwitch::OLD_TIMER_IVTE = 8;

void tick();

void ContextSwitch::requestSwitch()
{
	cout<<"CS::Switch requested"<<endl;
	switchRequested = 1;
}

void interrupt ContextSwitch::timer(...){

	if(!switchRequested)
	{
		if(counter==1)
		cout<<"CS::timer standard timer"<<endl<<counter<<endl;
		tick();
		oldTimer();
		PCB::sleepingList.tick();
		if(counter>0) counter--;
	}

	unsigned tempStackSegment;
	unsigned tempStackPointer;
	unsigned tempBasePointer;

	if(counter|| PCB::globalLock)
	cout<<"CS::timer counter = "<<counter<<" globalLock = "<<PCB::globalLock<<endl;

	if(!switchRequested && counter == 1 && PCB::globalLock > 0)
		{
		timePassed = 1;
		cout<<"CS::timer timePassed = 1\n";
		}

	if((counter == 0 && PCB::globalLock == 0) || switchRequested)
	{
		cout<<"CS::timer Switch requested"<<endl;
		#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tempStackSegment, ss
				mov tempStackPointer, sp
				mov tempBasePointer, bp
			}
		#endif


		PCB::running->stackSegment = tempStackSegment;
		PCB::running->stackPointer = tempStackPointer;
		PCB::running->basePointer = tempBasePointer;

		PCB::running->localLock = PCB::globalLock;

		if(PCB::running->status == PCB::RUNNING && PCB::running->thread != IdleThread::getIdleThread()){
			PCB::running->setStatus(PCB::READY);
			Scheduler::put(PCB::running);
		}

		PCB::running = Scheduler::get();

		if(PCB::running != 0)
		{
			cout<<"CS::timer running NOT NULL"<<endl;
		}

		if(PCB::running == 0){
			cout<<"CS::timer running NULL"<<endl;
			PCB::running = PCB::getPCBbyId(PCB::getIdleThreadId());
			cout<<"CS::timer running name = "<<PCB::running->name<<endl;
		}

		PCB::running->setStatus(PCB::RUNNING);
		PCB::globalLock = PCB::running->localLock;
		counter = PCB::running->timeSlice;

		tempStackSegment = PCB::running->stackSegment;
		tempStackPointer = PCB::running->stackPointer;
		tempBasePointer = PCB::running->basePointer;

		counter = PCB::running->timeSlice;

		#ifndef BCC_BLOCK_IGNORE
			asm{
				mov ss, tempStackSegment
				mov sp, tempStackPointer
				mov bp, tempBasePointer
			}
		#endif

		switchRequested = 0;
	}

}

void ContextSwitch::inic()
{
	#ifndef BCC_BLOCK_IGNORE
		asm pushf;
		asm cli;
		oldTimer = getvect(OLD_TIMER_IVTE);
		setvect(OLD_TIMER_IVTE, timer);
		asm popf;
	#endif
}

void ContextSwitch::restore()
{
	#ifndef BCC_BLOCK_IGNORE
		asm pushf;
		asm cli;
		setvect(OLD_TIMER_IVTE, oldTimer);
		asm popf;
	#endif
}
