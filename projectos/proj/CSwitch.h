#ifndef __CSWITCH_H_
#define __CSWITCH_H_

#include "include.h"

class ContextSwitch {
public:
	static void requestSwitch();
	static void interrupt timer(...);
	static void inic();
private:
	ContextSwitch();
	volatile static int switchRequested;
	volatile static Time counter;
	unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutina
};

#endif /* __CSWITCH_H_ */
