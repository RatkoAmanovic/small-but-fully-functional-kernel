#include "IdleThrd.h"

IdleThread* IdleThread::idleThread = 0;

IdleThread::IdleThread() : Thread(0,1,'i') {}

IdleThread::~IdleThread() {}

void IdleThread::run() {
	while(1);
}

IdleThread* IdleThread::getIdleThread() {
	if(idleThread==0) idleThread = new IdleThread();
	return idleThread;
}

