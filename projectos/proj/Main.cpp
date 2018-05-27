// File: main.cpp
#include <iostream.h>
#include <stdlib.h>
#include "Thread.h"
#include "PCB.h"
#include "MainThrd.h"
#include "CSwitch.h"
#include "IdleThrd.h"
#include "threadA.h"

int main(int argc, char *argv[]) {

	cout << "Hello World!" << endl;
//	MainThread::mainThread->setUserMainArguments(argc, argv);

	PCB* mainPCB = new PCB(0,0,1, 'm');
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	IdleThread::getIdleThread();

	cout<<"Main::main id = 0 = "<<PCB::pcbList.getById(0)->getId()<<endl;
	cout<<"Main::main id = 1 = "<<PCB::pcbList.getById(1)->getId()<<endl;

	ContextSwitch::inic();

	cout <<"CS::inic()"<<endl;



	ThreadA* niti = new ThreadA();

	cout <<"TA niti"<<endl;


	niti->start();
	cout <<"Start niti"<<endl;

	dispatch();

	cout<<"WTC niti"<<endl;

	//MainThread::mainThread->waitToComplete();

	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	cout <<"CS::restore"<<endl;
//	delete mainPCB;
//	delete MainThread::mainThread;

	cout << endl << "Good Bye World!" << endl;

	return 0;
}
