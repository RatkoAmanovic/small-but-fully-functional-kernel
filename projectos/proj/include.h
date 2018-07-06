#ifndef __INCLUDE_H_
#define __INCLUDE_H_

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef unsigned char IVTNo;

typedef void interrupt (*InterruptFunction)(...);

typedef void (*Function)();

#define lock PCB::globalLock++;
#define unlock PCB::globalLock--; \
if(PCB::globalLock == 0 && ContextSwitch::timePassed == 1) \
{ ContextSwitch::timePassed = 0; dispatch(); }

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2; // default = 2*55ms

static volatile unsigned helperOff = 0;
static volatile unsigned helperSeg = 0;

#endif /* __INCLUDE_H_ */
