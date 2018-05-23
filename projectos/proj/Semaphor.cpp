#include "Semaphor.h"

Semaphore::Semaphore(int init) {
	myImpl = 0;
}

Semaphore::~Semaphore() {
}

int Semaphore::wait(int i)
{
	return 0;
}

void Semaphore::signal()
{
	return;
}
