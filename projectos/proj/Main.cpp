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

//	cout<<"Pravi main"<<endl;
//	MainThread::getMainThread();
//
//	cout<<"Postavi parametre main"<<endl;
//	MainThread::mainThread->setUserMainArguments(argc, argv);

	cout<<"Pravi mainpcb"<<endl;
	PCB* mainPCB = new PCB(0,0,1);
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	IdleThread::getIdleThread();
	cout<<"prosao idle"<<endl;

	ContextSwitch::inic();

	cout<<"Pravi a"<<endl;
	ThreadA** niz = new ThreadA*[100];

	   for (int i = 0; i<100; i++){
		   niz[i] = new ThreadA();
		   niz[i]->start();
	   }
	   for(int j = 0; j<200; j++){
		   niz[j]->waitToComplete();
	   }

	   cout<<"Finished All"<<endl<<endl<<endl<<endl<<endl;
//	ThreadA* a = new ThreadA();
//	a->start();
//	a->waitToComplete();


//
//	MainThread::mainThread->waitToComplete();
//
//	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	delete mainPCB;
//	delete MainThread::mainThread;
	cout<<"KRAJ"<<endl;
	return 0;
}
