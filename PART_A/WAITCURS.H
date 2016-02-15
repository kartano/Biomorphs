/*======================================

TWaitCursor INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TCursor
======================================*/
#ifndef WAIT_CURSOR
#define WAIT_CURSOR

#include <owl/gdiobjec.h>

class TWaitCursor : public TCursor
{
  public:

    TWaitCursor(bool StartWait = true);
    ~TWaitCursor();
    void Wait() {OldCursor=SetCursor(*this);};
    void Done();

  private:

    HCURSOR OldCursor;
};

#endif