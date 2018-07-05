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

#define SYSTEM_CALL\
	unsigned helperSegment = FP_SEG(helper);\
	unsigned helperOffset = FP_OFF(helper);\
	asm push cx;\
	asm push dx;\
	asm mov cx, helperSegment;\
	asm mov dx, helperOffset;\
	cout<<"Seg "<<helperSegment<<" OFF "<<helperOffset<<endl;\
	asm int 60h;\
	asm pop dx;\
	asm pop cx;

#define CONSTRUCTOR_SYSTEM_CALL\
	helper->stackSegment = FP_SEG(this);\
	helper->stackOffset = FP_OFF(this);\
	SYSTEM_CALL

#endif /* __INCLUDE_H_ */
