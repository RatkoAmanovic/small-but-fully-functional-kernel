#include "MainThrd.h"

MainThread* MainThread::mainThread = new MainThread();
char** MainThread::argumentValue = 0;
int MainThread::argumentCount = 0;
int MainThread::userMainReturnValue = 0;

MainThread::MainThread() : Thread(0,1) {
	cout<<"MT::const"<<endl;
}

MainThread::~MainThread() {
	waitToComplete();
}

int userMain(int argc, char *argv[]);

void MainThread::setUserMainArguments(int argc, char *argv[])
{
	cout<<"MT::setUserArgs args"<<endl;
	MainThread::argumentCount = argc;
	MainThread::argumentValue = argv;
}

MainThread* MainThread::getMainThread()
{
	return mainThread;
}

void MainThread::run()
{
	cout<<"MT::run user main ocu da se zove"<<endl;
	userMainReturnValue = userMain(argumentCount, argumentValue);
}
