#include "IdleThrd.h"
#include "PCB.h"

IdleThread* IdleThread::idleThread = 0;
PCB* IdleThread::idlePCB = 0;

IdleThread::IdleThread() : Thread(1, 1, 1) {
	idlePCB = new PCB(this, 0, 1);
}

IdleThread::~IdleThread() {
}

void IdleThread::run() {
	while (1) {
		for(int i = 0; i<100000;i++)
			for(int j = 0; j<1000;j++);
		cout<<"Idle"<<endl;
	}
}

IdleThread* IdleThread::getIdleThread() {
	if (idleThread == 0)
		idleThread = new IdleThread();
	return idleThread;
}

