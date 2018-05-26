#include "MainThrd.h"

MainThread* MainThread::mainThread = 0;
char** MainThread::argumentValue = 0;
int MainThread::argumentCount = 0;
int MainThread::userMainReturnValue = 0;

MainThread::MainThread() {}

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
	return mainThread;
}

void MainThread::run()
{
	userMainReturnValue = userMain(argumentCount, argumentValue);
}
