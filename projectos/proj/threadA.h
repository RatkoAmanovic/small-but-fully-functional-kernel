/*
 * threadA.h
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#ifndef THREADA_H_
#define THREADA_H_
#include <iostream.h>
#include "thread.h"
#include <dos.h>
#include "CSwitch.h"
#include "semaphor.h"
class ThreadA: public Thread{
private:
	   int id;
static int ID55;

public:

	ThreadA(StackSize stackSize = defaultStackSize, Time timeSlice  = defaultTimeSlice):Thread(stackSize,timeSlice),s(new Semaphore(0)){id = ID55++;}

	void run();


	Semaphore* s;

};

#endif /* THREADA_H_ */
