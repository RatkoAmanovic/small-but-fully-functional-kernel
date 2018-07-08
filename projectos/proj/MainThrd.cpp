#include "MainThrd.h"

MainThread* MainThread::mainThread = 0;
char** MainThread::argumentValue = 0;
int MainThread::argumentCount = 0;
int MainThread::userMainReturnValue = 0;

MainThread::MainThread() : Thread(defaultStackSize,1) {
//	cout<<"MT::const"<<endl;
}

MainThread::~MainThread() {
	waitToComplete();
}

int userMain(int argc, char *argv[]);

void MainThread::setUserMainArguments(int argc, char *argv[])
{
	MainThread::argumentCount = argc;
	MainThread::argumentValue = argv;
}

MainThread* MainThread::getMainThread()
{
	if(mainThread == 0)
		mainThread = new MainThread();
	return mainThread;
}

void MainThread::run()
{
//	cout<<"MT::run user main ocu da se zove"<<endl;
	userMainReturnValue = userMain(argumentCount, argumentValue);
}
