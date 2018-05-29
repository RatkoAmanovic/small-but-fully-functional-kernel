#ifndef __SEMAPLST_H_
#define __SEMAPLST_H_

#include <iostream.h>

class KernelSem;

class KernelSemList {
	public:
		KernelSemList();
		~KernelSemList();
		KernelSemList& insert(KernelSem *semaphore);
		void resumeAll();
		int isEmpty();
		KernelSem* takeFirst();
		KernelSem* getById(int id);
		void removeById(int id);
	private:
		typedef struct Elem{
			KernelSem *semaphore;
			Elem *next;
			Elem(KernelSem *semaphore) : semaphore(semaphore), next(0) {};
		};
		Elem *head, *tail;
};

#endif /* __SEMAPLST_H_ */
