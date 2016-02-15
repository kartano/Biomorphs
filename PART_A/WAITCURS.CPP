/*======================================

TWaitCursor IMPLEMENTATION

By Simon Mitchell (96878291)

  TWaitCursor class is used to change the standard
windows pointer cursor to an hourglass.

BASE CLASSES: TCursor
======================================*/

#include <owl/gdiobjec.h>
#include "waitcurs.h"

//-------------------------------------
// CONSTRUCTOR
//-------------------------------------

TWaitCursor::TWaitCursor (bool StartWait):TCursor(0,IDC_WAIT), OldCursor(0)
{
  if (StartWait)
    Wait();
}

//-------------------------------------
// DESTRUCTOR
//-------------------------------------

TWaitCursor::~TWaitCursor()
{
  Done();
}

//-------------------------------------
// Done
//
// Sets cursor to old cursor
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TWaitCursor::Done()
{
  if (OldCursor)
    SetCursor(OldCursor);
  OldCursor=0;
}

