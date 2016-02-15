/*======================================

ArrayClass INTERFACE

By Simon Mitchell (96878291)

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

private:

  // Traversal pointers

  CharNode *rootPtr, *currentPtr;

  // Total elements in the array

  int elements;

  void destroyArray();

public :

  ArrayClass();
  ~ArrayClass();

  void resetPtr();
  char getNext();
  void advancePtr();
  void addToArray(char);
  void emptyArray();
  void contentsOfArray();
  char getFromArray(int);
  int numElements();
  void set(int, char);
  void setCurrent(char);
  char whatsNext();

};
#endif
