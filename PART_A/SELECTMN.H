// selectionManager class INTERFACE

// By Simon Mitchell					96878291

// 27/3/98

#ifndef NATURAL_SELECTION_MANAGER
#define NATURAL_SELECTION_MANAGER

#include<time.h>
#include "anarray.h"
#include "interfac.h"

class selectionManager {

private:

	ArrayClass oriArray, evoArray;
	interface myInterface;

// Statisical information used for reports

	int generations;
	clock_t start, end, maxTime, minTime, diff, mean;

	int getRandom();
	void fillEvoArray();
	void fileText();
	void keyboardText();
	void evolve();
   void writeReport(char *);

public :

	 selectionManager();
	 ~selectionManager();

	 void run();
};

#endif

