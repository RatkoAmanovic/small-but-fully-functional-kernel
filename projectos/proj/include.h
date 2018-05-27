#ifndef __INCLUDE_H_
#define __INCLUDE_H_

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef unsigned char IVTNo;

typedef void interrupt (*Function)(...);

#define lock PCB::globalLock++;
#define unlock PCB::globalLock--; \
if(PCB::globalLock == 0 && ContextSwitch::timePassed == 1) \
{ ContextSwitch::timePassed = 0; dispatch(); }

#endif /* __INCLUDE_H_ */
