/*======================================
ArrayClass IMPLEMENTATION

By Simon Mitchell (96878291)

  The dynamic array class.

BASE CLASSES: None
======================================*/

#include "array.h"

//==============================
// CONSTRUCTOR
//==============================

ArrayClass::ArrayClass()
{
  rootPtr=currentPtr=NULL;
  elements=0;
}

//==============================
// DESTRUCTOR
//==============================

ArrayClass::~ArrayClass()
{
  destroyArray();
}

//==============================
// destroyArray
//
// Destroys all elements contained in the array.
//
// Receives: Nothing
//  Returns: Nothing
//==============================

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

//==============================
// addToArray
//
// Adds an element to the end of the array, updates current pointer
//
// NOTE: currentPtr does not need to be advanced for this method!!!!!!!
//
// Receives: Integer values for new array node
//  Returns: Nothing
//==============================

void ArrayClass::addToArray(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
  elements++;
  CharNode *newNode;
  newNode = new CharNode;
  newNode->nodeGenes[0]=a;
  newNode->nodeGenes[1]=b;
  newNode->nodeGenes[2]=c;
  newNode->nodeGenes[3]=d;
  newNode->nodeGenes[4]=e;
  newNode->nodeGenes[5]=f;
  newNode->nodeGenes[6]=g;
  newNode->nodeGenes[7]=h;
  newNode->nodeGenes[8]=i;
  newNode->nodeGenes[9]=j;
  newNode->nodeGenes[10]=k;

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

//==============================
// getNext
//
// Returns the next gene list in the array, using the sequential
// pointer
//
// Receives: Addresses to store gene values into
//  Returns: Nothing
//==============================

void ArrayClass::getNext(int &a, int&b, int &c, int &d, int &e, int &f, int &g, int &h, int &i, int &j, int &k)
{
  if (currentPtr!=NULL)
    {
      a=currentPtr->nodeGenes[0];
      b=currentPtr->nodeGenes[1];
      c=currentPtr->nodeGenes[2];
      d=currentPtr->nodeGenes[3];
      e=currentPtr->nodeGenes[4];
      f=currentPtr->nodeGenes[5];
      g=currentPtr->nodeGenes[6];
      h=currentPtr->nodeGenes[7];
      i=currentPtr->nodeGenes[8];
      j=currentPtr->nodeGenes[9];
      k=currentPtr->nodeGenes[10];
   }
}

//==============================
// saveContents
//
// Save the contents of the array to disk
//
// Receives: Filename
//  Returns: Nothing
//==============================

void ArrayClass::saveContents(char *fileName)
{
  ofstream ofs(fileName, ios::out|ios::binary);
  currentPtr=rootPtr;
  int a,b,c,d,e,f,g,h,i,j,k;
  while (currentPtr!=NULL)
    {
      a=currentPtr->nodeGenes[0];
      b=currentPtr->nodeGenes[1];
      c=currentPtr->nodeGenes[2];
      d=currentPtr->nodeGenes[3];
      e=currentPtr->nodeGenes[4];
      f=currentPtr->nodeGenes[5];
      g=currentPtr->nodeGenes[6];
      h=currentPtr->nodeGenes[7];
      i=currentPtr->nodeGenes[8];
      j=currentPtr->nodeGenes[9];
      k=currentPtr->nodeGenes[10];

      ofs.put((unsigned char)a);
      ofs.put((unsigned char)b);
      ofs.put((unsigned char)c);
      ofs.put((unsigned char)d);
      ofs.put((unsigned char)e);
      ofs.put((unsigned char)f);
      ofs.put((unsigned char)g);
      ofs.put((unsigned char)h);
      ofs.put((unsigned char)i);
      ofs.put((unsigned char)j);
      ofs.put((unsigned char)k);

      currentPtr=currentPtr->next;
    }
  ofs.close();
}

//==============================
// loadContents
//
// Load the contents of the array from disk
//
// Receives: Filename
//  Returns: Nothing
//==============================

void ArrayClass::loadContents(char *fileName)
{
  ifstream    ifs(fileName, ios::in|ios::binary);
  destroyArray();
  int a,b,c,d,e,f,g,h,i,j,k;
  while (!ifs.eof())
    {
       a=(unsigned char)ifs.get();
       b=(unsigned char)ifs.get();
       c=(unsigned char)ifs.get();
       d=(unsigned char)ifs.get();
       e=(unsigned char)ifs.get();
       f=(unsigned char)ifs.get();
       g=(unsigned char)ifs.get();
       h=(unsigned char)ifs.get();
       i=(unsigned char)ifs.get();
       j=(unsigned char)ifs.get();
       k=(unsigned char)ifs.get();
       addToArray(a,b,c,d,e,f,g,h,i,j,k);
    }
  ifs.close();
}
