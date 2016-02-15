/*======================================
Animator INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TWindow
======================================*/

#include <owl/uihelper.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/static.h>
#include <stdlib.h>
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/opensave.h>
#include <time.h>
#include <stdlib.h>
#include "biomorph.h"
#include "array.h"
#include "animator.rh"

#ifndef APPLICATION_INTERFACE
#define APPLICATION_INTERFACE

const int defR = 190;
const int defG = 190;
const int defB = 190;

class Interface : public TWindow
{

  public:

    Interface();
    ~Interface();
    void SetupWindow();
    void Paint(TDC&, bool, TRect&);
    void CloseWindow();
    void Animate();

  protected:

    ArrayClass *animationArray;

    TUIBorder *border;

    TButton *exit, *anim;

    TBiomorph *morph;

  DECLARE_RESPONSE_TABLE(Interface);
};

#endif

