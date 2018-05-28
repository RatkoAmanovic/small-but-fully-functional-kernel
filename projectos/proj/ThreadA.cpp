/*
 * ThreadA.cpp
 *
 *  Created on: May 11, 2018
 *      Author: OS1
 */

#include <iostream.h>
#include "threadA.h"
#include "include.h"
#include "PCB.h"


int ThreadA::ID55 = 0;


void ThreadA::run(){

	cout<<"TA:run EHEJ OVO TREBA DA RADI"<<endl;
	lock;
			for(int i= 0; i<5000;i++){
				if (i%1000 == 0){
		     	cout<<"nit"<<id<<" "<<i<<endl;
//		     	sleep(id);
				}
			}
	s->signal();
	unlock;
	  return;


}
