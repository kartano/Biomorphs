/*======================================

EvolutionManager IMPLEMENTATION

By Simon Mitchell (96878291)

  EvolutionManager is used to perform evolution using
two TExampleEdit objects

BASE CLASSES: None
======================================*/
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/opensave.h>
#include <stdlib.h>
#include <time.h>

#include "evolve.h"
#include "anarray.h"

//-------------------------------------
// CONSTRUCTOR
//-------------------------------------

EvolutionManager::EvolutionManager()
{
  randomize();
  oriArray = new ArrayClass();
  evoArray = new ArrayClass();
}

//-------------------------------------
// DESTRUCTOR
//-------------------------------------

EvolutionManager::~EvolutionManager()
{
  delete oriArray;
  delete evoArray;
}

//-------------------------------------
// evolveText
//
// Begin evolution process
//
// Receives: pointer to original text edit box,
//           pointer to evolving text edit box,
//           delay time between generations,
//           generation limit,
//           delay state,
//           show all generations state,
//           evolution limit state
//  Returns: Nothing
//-------------------------------------

void EvolutionManager::evolveText
(
  TExampleEdit *newOriginal,
  TExampleEdit *newEvolving,
  int newDelayTime,
  int newGenerationLimit,
  bool newNoDelay,
  bool newAllGenerations,
  bool newEvolveToLimit)
{
  original=newOriginal;
  evolving=newEvolving;
  generationLimit=newGenerationLimit;
  evolveToLimit=newEvolveToLimit;
  noDelay=newNoDelay;
  delayTime=newDelayTime;
  showAllGenerations=newAllGenerations;
  oriArray->emptyArray();
  evoArray->emptyArray();
  fillEvoEdit();
  waitCursor = new TWaitCursor(false);
  waitCursor->Wait();
  maxchanges=0;
  minchanges=oriArray->numElements()+1;
  generations=0;
  count=oriArray->numElements();
  totalTime=0;
//  start=clock();
};

//-------------------------------------
// fillEvoEdit()
//
// Fills evolving text array class with the
// same amount of random text as what the
// original text edit box contains
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void EvolutionManager::fillEvoEdit()
{
  oriArray->resetPtr();
  evoArray->resetPtr();
  oriBuffer = original->returnBuffer();
  int count=0;
  while (oriBuffer[count]!=0)
  {
        if ((oriBuffer[count]>126)||(oriBuffer[count]<32))
          oriArray->addToArray('\n');
        else
          oriArray->addToArray(oriBuffer[count]);
        evoArray->addToArray(getRandom());
    count++;
  }
  original->resetBuffer();
}

//-------------------------------------
// displayGeneration
//
// Copies evolving text array to the evolving text edit buffer
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void EvolutionManager::displayGeneration()
{
  evolving->Clear();
  evoBuffer=evolving->returnBuffer();
  evoArray->resetPtr();
  char evoChar;
  int count = evoArray->numElements();
  int bufferCount=0;
  bool lastWasLF = false;
  for (int i=0; i!=count; i++)
    {
      evoChar=evoArray->getNext();
      if (evoChar=='\n')
        {
          if (lastWasLF)
            {
              evoArray->advancePtr();
              lastWasLF=false;
            }
          else
            {
              evoBuffer[bufferCount++]='\r';
              evoBuffer[bufferCount++]='\n';
              evoArray->advancePtr();
              lastWasLF= true;
            }
        }
     else
       {
         lastWasLF=false;
          evoBuffer[bufferCount++]=evoChar;
          evoArray->advancePtr();
       }
    }
  evoBuffer[bufferCount]=0;
  evoArray->resetPtr();
  evolving->resetBuffer();
  evolving->NotifyParent(CN_UPDATE);
  evolving->UpdateDisplay();
}

//-------------------------------------
// evolveTheText
//
// Carries out evolution process on evolving text array
// using current settings
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

bool EvolutionManager::evolveTheText()
{
  notFinished=true;
  maxcount =0;

  // MAXCOUNT here is used to determine how many characters were
  // changed in the RESULT array.
  // If MAXCOUNT == COUNT, then we changed them all, and we're not
  // finished. If MAXCOUNT==0, nothing was changed and we can exit.

  maxcount=0;
  oriChar=evoChar=' ';
  oriArray->resetPtr();
  evoArray->resetPtr();

  start=clock();

  for (int i=0;i!=count;i++)
    {
	   evoChar=evoArray->getNext();
	   oriChar=oriArray->getNext();
	   if (evoChar!=oriChar)
        {
          evoArray->setCurrent(getRandom());
	  		 maxcount++;
	  	  }
	   evoArray->advancePtr();
      oriArray->advancePtr();
    }
  generations++;
  if (noDelay==false)
    {
      wend=0;
      wstart=clock();
      while (wend<wstart+(delayTime*CLK_TCK))
        wend=clock();
    }
  if (showAllGenerations)
    displayGeneration();
  if (maxchanges<maxcount)
    maxchanges=maxcount;
  if (minchanges>maxcount)
    minchanges=maxcount;
  if (maxcount==0)
    notFinished=false;
  if ((evolveToLimit)&&(generationLimit==generations))
    notFinished=false;

// RETURNS "TRUE" WHEN EVOLUTION COMPLETE

  end = clock();

  totalTime+=end-start;

  return notFinished;
}

//-------------------------------------
// Finish
//
// Resets all the evolution attributes when evolution is complete
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void EvolutionManager::Finish()
{
  waitCursor->Done();
  displayGeneration();
};

//-------------------------------------
// getStates
//
// Sets cursor to an hourglass
//
// Receives: Address of seconds variable,
//           address of generation count variable,
//           address of maximum changes variable,
//           address of minimum changes variable
//  Returns: Nothing
//-------------------------------------

void EvolutionManager::getStats
(int &seconds,
 int &gens,
 int &maxch,
 int &minch)
{
  seconds=totalTime/CLK_TCK;
  gens=generations;
  maxch=maxchanges;
  minch=minchanges;
}

//-------------------------------------
// getRandom
//
//  Generations a random char in printable ascii range
//
// NOTES: This method will also return /n and /r characters
// which are represented here with ascii codes 127 and 128
//
// Receives: Nothing
//  Returns: Random char in printable ascii range
//-------------------------------------

int EvolutionManager::getRandom()
{
  int myValue;
  myValue=random(97)+32;
  if (myValue==127)       // use code 127 for \n char
	 myValue='\n';
  if (myValue==128)       // use code 128 for \r char
    myValue='\r';
  return myValue;
}

