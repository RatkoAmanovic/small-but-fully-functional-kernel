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

	cout<<"Pravi main"<<endl;
	MainThread::getMainThread();

	cout<<"Postavi parametre main"<<endl;
	MainThread::mainThread->setUserMainArguments(argc, argv);

	cout<<"Pravi mainpcb"<<endl;
	PCB* mainPCB = new PCB(0,0,1);
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	IdleThread::getIdleThread();
	cout<<"prosao idle"<<endl;

	ContextSwitch::inic();

	cout<<"Pravi a"<<endl;

//
//	int numOfThreads = 200;
//	ThreadA** niz = new ThreadA*[numOfThreads];
//
//
//	   for (int i = 0; i<numOfThreads; i++){
//		   niz[i] = new ThreadA();
//		   niz[i]->start();
//	   }
//	   cout<<"PROSLI STARTOVI###################################################"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
//	   for (int k = 0; k<numOfThreads; k++) niz[k]->s->wait(0);
//
//	   cout<<"PROSLI WAITOVI###################################################"<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
//	  	    for (int j = 0; j<numOfThreads; niz[j++]->waitToComplete());
//	   for(int j = 0; j<50; j++){
//		   niz[j]->waitToComplete();
//		   cout<<"MAIN::wtc - "<<j<<endl;
//	   }
//	   niz[5]->waitToComplete();
//	   cout<<"PROSLI WAITTOKOMPLITOVI"<<endl<<endl<<endl;
//
//	   cout<<"Finished All"<<endl<<endl<<endl<<endl<<endl;
//	ThreadA* a = new ThreadA();
//	a->start();
//	a->waitToComplete();


//
	MainThread::mainThread->waitToComplete();

	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	delete mainPCB;
//	delete MainThread::mainThread;
	cout<<"KRAJ"<<endl;
	return 0;
}
