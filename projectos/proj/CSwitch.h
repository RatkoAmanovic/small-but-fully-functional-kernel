#ifndef __CSWITCH_H_
#define __CSWITCH_H_

#include "include.h"

class ContextSwitch {
public:

	friend class PCB;
	friend class KernelThread;

	static void interrupt timer(...);
	static void requestSwitch();
	static void inic();
	static void restore();
	volatile static int timePassed;
private:
	ContextSwitch();
	volatile static int switchRequested;
	volatile static Time counter;
	static InterruptFunction oldTimer;

	static const int OLD_TIMER_IVTE;
};

#endif /* __CSWITCH_H_ */
