/*======================================

EvolutionManager INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/
#include <time.h>
#include "waitcurs.h"
#include "editexam.h"
#include "anarray.h"

#ifndef EVOLUTION_MANAGER
#define EVOLUTION_MANAGER

class EvolutionManager {

  public:

    EvolutionManager();
    ~EvolutionManager();
    void evolveText(TExampleEdit *,TExampleEdit *,int,int,bool,bool,bool);
    void getStats (int &, int &, int &, int&);
    bool evolveTheText();
    void Finish();

  private:

    char far *oriBuffer, *evoBuffer;
    unsigned lengthEvo, lengthOri;

    // Setting information

    int generationLimit;
    int delayTime;
    bool evolveToLimit;
    bool noDelay;
    bool showAllGenerations;

    int count, maxcount;
    bool notFinished;
    char oriChar, evoChar;

    // GUI elements

    TExampleEdit *evolving, *original;
    TWaitCursor *waitCursor;
    ArrayClass *evoArray, *oriArray;

    // General methods

    void fillEvoEdit();
    void displayGeneration();

    // Statistics information

    clock_t start, end, wstart, wend, totalTime;
    int generations, maxchanges, minchanges;

    int getRandom();
};

#endif
