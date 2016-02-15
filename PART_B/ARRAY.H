/*======================================
ArrayClass INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/
#include<iostream.h>
#include<stddef.h>
#include<fstream.h>
#include<stdlib.h>

// Include the definition for each node in the array

#include "animstruc.h"

#ifndef DYNAMIC_ARRAY_CLASS
#define DYNAMIC_ARRAY_CLASS

class ArrayClass {

public :

  ArrayClass();
  ~ArrayClass();

  void resetPtr() {currentPtr=rootPtr;};
  void getNext(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
  void advancePtr(){if (currentPtr->next!=NULL)currentPtr=currentPtr->next;};
  void addToArray(int, int, int, int, int, int, int, int, int, int, int);
  void emptyArray() {destroyArray();};
  int numElements() {return elements;};
  void saveContents(char *);
  void loadContents(char *);

private:

  void destroyArray();

  // Traversal pointers

  CharNode *rootPtr, *currentPtr;

  // Total elements in the array

  int elements;
};

#endif
