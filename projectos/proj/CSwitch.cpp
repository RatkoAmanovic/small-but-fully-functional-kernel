#include "CSwitch.h"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "IdleThrd.h"
#include "Thread.h"
#include "KernlThr.h"

volatile int ContextSwitch::switchRequested = 0;
volatile Time ContextSwitch::counter = 0;
InterruptFunction ContextSwitch::oldTimer = 0;
volatile int ContextSwitch::timePassed = 0;
volatile unsigned tempStackSegment = 0;
volatile unsigned tempStackPointer = 0;
volatile unsigned tempBasePointer = 0;

const int ContextSwitch::OLD_TIMER_IVTE = 0x8;

void tick();

void ContextSwitch::requestSwitch() {
	switchRequested = 1;
}

void interrupt ContextSwitch::timer(...) {
	if(PCB::running->noTimer==1) {
		if(!switchRequested) {
			tick();
			oldTimer();
			PCB::sleepingList.tick();
			return;
		}
		else {
			dispatch();
			switchRequested = 0;
			return;
		}

	}

	if(!switchRequested) {
		tick();
		oldTimer();
		PCB::sleepingList.tick();
		if(counter>0) counter--;
	}

	if(!switchRequested && counter == 1 && PCB::globalLock > 0) {
		timePassed = 1;
		return;
	}

	if((counter == 0 && PCB::globalLock == 0) || switchRequested) {
		dispatch();
		switchRequested = 0;
		return;
	}

}


void ContextSwitch::inic() {
	#ifndef BCC_BLOCK_IGNORE
		asm pushf;
		asm cli;
		oldTimer = getvect(OLD_TIMER_IVTE);
		setvect(OLD_TIMER_IVTE, timer);
		asm popf;
	#endif
}

void ContextSwitch::restore() {
	#ifndef BCC_BLOCK_IGNORE
		asm pushf;
		asm cli;
		setvect(OLD_TIMER_IVTE, oldTimer);
		asm popf;
	#endif
}
