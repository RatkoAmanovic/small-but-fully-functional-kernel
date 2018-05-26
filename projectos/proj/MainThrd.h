#ifndef __MAINTHRD_H_
#define __MAINTHRD_H_

#include "Thread.h"

class MainThread : public Thread{

	friend int main(int argc, char *argv[]);

public:
	~MainThread();
	static void setUserMainArguments(int argc, char *argv[]);
	static MainThread* getMainThread();
	void run();
private:
	MainThread();

	static MainThread* mainThread;
	static int argumentCount;
	static char **argumentValue;
	static int userMainReturnValue;

};

#endif /* __MAINTHRD_H_ */
