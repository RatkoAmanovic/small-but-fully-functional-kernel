#ifndef __IDLETHRD_H_
#define __IDLETHRD_H_

#include "Thread.h"

class IdleThread : public Thread{
	public:

		friend class PCB;

		IdleThread();
		~IdleThread();
		void run();
		static IdleThread* getIdleThread();
	private:
		static IdleThread *idleThread;
		static PCB* idlePCB;
};

#endif /* __IDLETHRD_H_ */
