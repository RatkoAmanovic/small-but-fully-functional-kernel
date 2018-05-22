#ifndef __EVENT_H_
#define __EVENT_H_

#include "include.h"

class KernelEv;

class Event {
	public:
		Event (IVTNo ivtNo);
		~Event ();
		void wait ();
	protected:
		friend class KernelEv;
		void signal(); // can call KernelEv
	private:
		KernelEv* myImpl;
};
#endif //__EVENT_H_
