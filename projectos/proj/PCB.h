#ifndef __PCB_H_
#define __PCB_H_

#include <iostream.h>
#include <dos.h>

class PCB
{
public:
	enum Status{
		RUNNING,READY,BLOCKED,FINISHED
	};

private:
	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned timeSlice;
	Status status;
};

#endif //__PCB_H_
