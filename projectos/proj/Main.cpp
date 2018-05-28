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

//PREPAREENTRY(9,1);
//
//class Test : public Thread
//{
//	void run()
//	{
//		Event* e = new Event(9);
//		while(1)
//		{
//			e->wait();
//			cout<<"Test::run::while odblokirao sam se"<<endl;
//		}
//	}
//};

int main(int argc, char *argv[]) {

	cout << "Hello World!" << endl;

	MainThread::mainThread->setUserMainArguments(argc, argv);

	PCB* mainPCB = new PCB(0,0,1, 'm');
	mainPCB->setStatus(PCB::RUNNING);
	PCB::running = mainPCB;

	MainThread::mainThread->start();

	IdleThread::getIdleThread();

	ContextSwitch::inic();

	cout <<"CS::inic()"<<endl;

//	Test* t = new Test();
//	t->start();
//	t->waitToComplete();

//	ThreadA** niz = new ThreadA*[100];
//
//	   for (int i = 0; i<100; i++){
//		   niz[i] = new ThreadA();
//		   niz[i]->start();
//	   }
//
//	   for (int k = 0; k<100; k++) niz[k]->s->wait(0);
//
//	    for (int j = 0; j<100; niz[j++]->waitToComplete());
//
//	/*for (int k =0; k<100;delete niz[k++]);
//		delete niz;*/
//
//	    cout<<"Main::main id = 0 = "<<PCB::pcbList.getById(0)->getId()<<endl<<PCB::pcbList.getById(0)->name<<endl;
//	    cout<<"Main::main id = 1 = "<<PCB::pcbList.getById(1)->getId()<<endl<<PCB::pcbList.getById(1)->name<<endl;



	MainThread::mainThread->waitToComplete();

	int returnValue = MainThread::userMainReturnValue;

	ContextSwitch::restore();

	cout <<"CS::restore"<<endl;
	delete mainPCB;
	delete MainThread::mainThread;

	cout << endl << "Good Bye World!" << endl;

	while(1);
	return 0;
}
