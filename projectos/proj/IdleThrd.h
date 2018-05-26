#ifndef __IDLETHRD_H_
#define __IDLETHRD_H_

#include "Thread.h"

class IdleThread : public Thread{
	public:
		IdleThread();
		~IdleThread();
		void run();
};

#endif /* __IDLETHRD_H_ */
