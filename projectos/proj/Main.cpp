// File: main.cpp
#include <iostream.h>
#include <stdlib.h>
#include "thread.h"
#include "pcb.h"
int main(int argc, char *argv[]) {

	cout << "Hello World!" << endl;

	// Prepare the PCB for the main function
	// It doesn't allocate a stack, and operates on the system stack
	PCB *main_pcb = new PCB(0, 0, 1);
	main_pcb->setStatus(PCB::RUNNING);


	cout << endl << "Good Bye World!" << endl;

	// Delete the Kernel threads, and the Kernel itself:
	delete main_pcb;

	return 0;
}
