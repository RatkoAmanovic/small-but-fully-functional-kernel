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

//	PCB* mainPCB = new PCB(0,0,1);
//	mainPCB->setStatus(PCB::RUNNING);
//	PCB::running = mainPCB;

	ContextSwitch::inic();

	ThreadA* niti = new ThreadA[1];

	for (int i = 0; i < 1; ++i) {
		niti[i].start();
	}

	for (int j = 0; j < 1; ++j) {
		niti[j].waitToComplete();
	}
//	MainThread::mainThread->waitToComplete();

//	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

//	delete mainPCB;
	delete MainThread::mainThread;

	cout << endl << "Good Bye World!" << endl;

	return 0;
}
