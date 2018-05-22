#ifndef __INCLUDE_H_
#define __INCLUDE_H_

typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef unsigned char IVTNo;

#define lock PCB::globalLock++
#define unlock PCB::globalLock--

#endif /* __INCLUDE_H_ */
