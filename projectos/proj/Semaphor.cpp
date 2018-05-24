#include "Semaphor.h"
#include "include.h"
#include "KernlSem.h"
#include "PCB.h"

Semaphore::Semaphore(int init) {
	lock;
	myImpl = new KernelSem(init);
	unlock;
}

Semaphore::~Semaphore() {
	lock;
	delete myImpl;
	unlock;
}

int Semaphore::wait(int toBlock)
{
	int temp;
	lock;
	if(!toBlock) {
		if (val()<=0)
			return -1;
	}
	temp = myImpl->wait(toBlock);
	unlock;
	return temp;
}

void Semaphore::signal() {
	lock;
	myImpl->signal();
	unlock;
}

int Semaphore::val() const {
	int temp;
	lock;
	temp = myImpl->val();
	unlock;
	return temp;
}
