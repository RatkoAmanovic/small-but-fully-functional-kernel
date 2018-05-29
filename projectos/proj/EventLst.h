#ifndef __EVENTLST_H_
#define __EVENTLST_H_

#include <iostream.h>

class KernelEv;

class KernelEvList {
	public:
		KernelEvList();
		~KernelEvList();
		KernelEvList& insert(KernelEv *event);
		void resumeAll();
		int isEmpty();
		KernelEv* takeFirst();
		KernelEv* getById(int id);
		void removeById(int id);
	private:
		typedef struct Elem{
			KernelEv *event;
			Elem *next;
			Elem(KernelEv *event) : event(event), next(0) {};
		};
		Elem *head, *tail;
};

#endif /* __EVENTLST_H_ */
