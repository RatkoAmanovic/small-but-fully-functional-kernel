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
//#include "TestThr.h"
#include "KernlThr.h"


int main(int argc, char *argv[]) {
	KernelThread::inic();

	cout<<"Pravi kernel"<<endl;
	KernelThread::getKernelThread();


	IdleThread::getIdleThread();
	cout<<"prosao idle"<<endl;


	cout<<"Postavi parametre main"<<endl;
	MainThread::mainThread->setUserMainArguments(argc, argv);

	cout<<"Pravi mainpcb"<<endl;
	PCB* mainPCB = new PCB(0,0,1);
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	cout<<"Pravi main"<<endl;
	MainThread::getMainThread()->start();

	ContextSwitch::inic();

	MainThread::mainThread->waitToComplete();

	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	delete mainPCB;
	delete MainThread::mainThread;
	cout<<"KRAJ"<<endl;
	return 0;
}
