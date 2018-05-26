#ifndef __CSWITCH_H_
#define __CSWITCH_H_

#include "include.h"

class ContextSwitch {
public:

	friend class PCB;

	static void requestSwitch();
	static void interrupt timer(...);
	static void inic();
	static void restore();

	volatile static int timeSlicePassed;
private:
	ContextSwitch();
	volatile static int switchRequested;
	volatile static Time counter;
	volatile static Function oldTimer;

	static const int OLD_TIMER_IVTE;
};

#endif /* __CSWITCH_H_ */
