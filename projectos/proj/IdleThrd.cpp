#include "IdleThrd.h"

IdleThread::IdleThread() : Thread(0,1) {}

IdleThread::~IdleThread() {}

void IdleThread::run()
{
	while(1);
}
