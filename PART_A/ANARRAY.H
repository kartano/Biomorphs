/*======================================

ArrayClass INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/
#include<iostream.h>
#include<stddef.h>
#include<iostream.h>
#include<stdlib.h>

#ifndef DYNAMIC_ARRAY_CLASS
#define DYNAMIC_ARRAY_CLASS

// Definition of each array node

struct CharNode {

  CharNode *last;
  CharNode *next;
  char myChar;
};

class ArrayClass {

public :

  ArrayClass();
  ~ArrayClass();

  void resetPtr() {currentPtr=rootPtr;};
  char getNext();
  void advancePtr(){if (currentPtr->next!=NULL)currentPtr=currentPtr->next;};
  void addToArray(char);
  void emptyArray() {destroyArray();};
  void contentsOfArray();
  char getFromArray(int);
  int numElements() {return elements;};
  void set(int, char);
  void setCurrent(char newChar) {currentPtr->myChar=newChar;};
  char whatsNext();


private:

  void destroyArray();

  // Traversal pointers

  CharNode *rootPtr, *currentPtr;

  // Total elements in the array

  int elements;
};

#endif
