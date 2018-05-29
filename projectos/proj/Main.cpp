// File: main.cpp
#include <iostream.h>
#include <stdlib.h>
#include "Thread.h"
#include "PCB.h"
#include "MainThrd.h"
#include "CSwitch.h"
#include "IdleThrd.h"
#include "threadA.h"
#include "IVTEntry.h"
#include "Event.h"
#include "KernlThr.h"


int main(int argc, char *argv[]) {
	KernelThread::inic();

	KernelThread::getKernelThread();

	MainThread::mainThread->setUserMainArguments(argc, argv);

	PCB* mainPCB = new PCB(0,0,1);
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	cout<<"M:: before idle"<<endl;

	IdleThread::getIdleThread();


	ContextSwitch::inic();

	MainThread::mainThread->waitToComplete();

	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	delete mainPCB;
	delete MainThread::mainThread;
	return 0;
}
