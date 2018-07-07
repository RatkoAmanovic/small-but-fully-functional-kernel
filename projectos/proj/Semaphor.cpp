#include "Semaphor.h"
#include "include.h"
#include "KernlSem.h"
#include "PCB.h"
#include "CSwitch.h"
#include "HelpStrc.h"
#include "KernlThr.h"

Semaphore::Semaphore(int init) {
	Helper* helper = new Helper();
	helper->function = semaphoreConstruct;
	helper->init = init;
	systemCall(helper);
	kernelSemId = helper->id;
	delete helper;
}

Semaphore::~Semaphore() {
	Helper* helper = new Helper();
	helper->function = semaphoreDestruct;
	helper->id = kernelSemId;
	systemCall(helper);
	delete helper;
}

int Semaphore::wait(int toBlock) {
	cout<<"S::Wait"<<endl;
	int temp;
	if(!toBlock) {
		if (val()<=0){
			cout<<"Trebalo bi da se vrati ovde"<<endl;
			return -1;
		}
	}
	Helper* helper = new Helper();
	helper->function = semaphoreWait;
	helper->id = kernelSemId;
	systemCall(helper);
	temp = helper->init;
	delete helper;
	return temp;
}

void Semaphore::signal() {
	Helper* helper = new Helper();
	helper->function = semaphoreSignal;
	helper->id = kernelSemId;
	systemCall(helper);
	delete helper;
}

int Semaphore::val() const {
	cout<<"S::Val"<<endl;
	int temp;
	Helper* helper = new Helper();
	helper->function = semaphoreValue;
	helper->id = kernelSemId;
	systemCall(helper);
	temp = helper->init;
	delete helper;
	cout<<"S::Val returned "<<temp<<endl;
	return temp;
}

