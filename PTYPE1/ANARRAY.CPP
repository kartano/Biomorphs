/*======================================

ArrayClass IMPLEMENTATION

By Simon Mitchell (96878291)

  The dynamic array class.

BASE CLASSES: None
======================================*/
#include<iostream.h>
#include<stddef.h>
#include<iostream.h>
#include"anarray.h"

//-------------------------------
// CONSTRUCTOR
//-------------------------------

ArrayClass::ArrayClass()
{
  rootPtr=currentPtr=NULL;
  elements=0;
}

//-------------------------------
// DESTRUCTOR
//-------------------------------

ArrayClass::~ArrayClass()
{
  destroyArray();
}

//-------------------------------
// destroyArray
//
// Destroys all elements contained in the array.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------

void ArrayClass::destroyArray()
{
  CharNode *delPtr, *nextPtr;
  nextPtr=rootPtr;
  if (rootPtr!=NULL)
	 {
		delPtr=rootPtr;
		while(nextPtr!=NULL)
		  {
			 nextPtr=delPtr->next;
			 delete[] delPtr;
			 delPtr=nextPtr;
		  }
	 }
  rootPtr=currentPtr=NULL;
  elements=0;
}

//-------------------------------
// resetPtr
//
// Resets point for sequential traversal of array back to the root
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------

void ArrayClass::resetPtr() {currentPtr=rootPtr;}

//-------------------------------
// addToArray
//
// Adds an element to the end of the array, updates current pointer
//
// NOTE: currentPtr does not need to be advanced for this method!!!!!!!
//
// Receives: Char to add to list
//  Returns: Nothing
//-------------------------------

void ArrayClass::addToArray(char newChar)
{
  elements++;
  CharNode *newNode;
  newNode = new CharNode;
  newNode->myChar=newChar;

// If rootPtr==NULL, the array is empty. Make the new node the root node.

  if (rootPtr==NULL)
	 {
		rootPtr=newNode;
		newNode->next=NULL;
		newNode->last=NULL;
		currentPtr=newNode;
	 }

// Otherwise, tack it onto the end of currentPtr.

  else
	 {
		currentPtr->next=newNode;
		newNode->last=currentPtr;
		newNode->next=NULL;
		currentPtr=newNode;
	 }
}

//-------------------------------
// emptyArray
//
// Public function allowing access to destoryArray (which would normally
// only be called by the class destructor). It empties the array of all
// elements.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------

void ArrayClass::emptyArray() {destroyArray();}

//-------------------------------
// contentsOfArray
//
// Displays contents of entire array, start to finish
// to standard output
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------

void ArrayClass::contentsOfArray()
{
  resetPtr();
  char buffer;
  buffer=' ';
  while (buffer!=NULL)
	 {
		buffer=getNext();
		if (buffer!=NULL)
		  {
			 cout << buffer;
			 advancePtr();
		  }
	 }
}

//-------------------------------
// getFromArray
//
// Retrieves an element stored at position <place> in the array
//
// Receives: Index to node to return value from
//  Returns: Char at index position in the list
//-------------------------------

char ArrayClass::getFromArray(int place)
{
  if (place>elements)
	 cerr << "Index exceeds length of list!\n";
  else
	 {
		CharNode *ptr;
		ptr=rootPtr;
		while (place!=0)
		{
		  ptr=ptr->next;
		  place--;
		}
		return ptr->myChar;
	 }
}

//-------------------------------
// getNext
//
// Returns the next char along in the array, using the sequential
// pointer
//
// Receives: Nothing
//  Returns: Char in current node
//-------------------------------

char ArrayClass::getNext()
{
  if (currentPtr!=NULL)
	 return currentPtr->myChar;
  else
	 return NULL;
}

//-------------------------------
// advancePtr
//
// Advances currentPtr to the next node in the array
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------

void ArrayClass::advancePtr()
{
  if (currentPtr->next!=NULL)
    currentPtr=currentPtr->next;
}

//-------------------------------
// numElements
//
// Returns the number of elements in the array
//
// Receives: Nothing
//  Returns: Number of elements in the list
//-------------------------------

int ArrayClass::numElements() {return elements;}

//-------------------------------
// set
//
// Changes the char stored in a particular node
//
// Receives: Index to node for change, new char to replace old char
//  Returns: Nothing
//-------------------------------

void ArrayClass::set(int place, char newChar)
{
  if (place>elements)
	 cerr << "Index exceeds length of list!\n";
  else
	 {
		CharNode *ptr;
		ptr=rootPtr;
		while (place!=0)
		{
		  ptr=ptr->next;
		  place--;
		}
		ptr->myChar=newChar;
	 }
}

//-------------------------------
// setCurrent
//
// Changes value of node at currentPtr
//
// Receives: New char
//  Returns: Nothing
//-------------------------------

void ArrayClass::setCurrent(char newChar) {currentPtr->myChar=newChar;}

//-------------------------------
// whatsNext
//
// Returns the next char along in the array without
// advancing the pointer. Returns NULL if there are no
// nodes further down the array (I.E: We are at the end of
// the array)
//
// Receives: Nothing
//  Returns: Next character or NULL
//-------------------------------

char ArrayClass::whatsNext()
{
  if (rootPtr==NULL)
    return NULL;
  if (currentPtr->next!=NULL)
    return currentPtr->next->myChar;
  else
    return NULL;
}

