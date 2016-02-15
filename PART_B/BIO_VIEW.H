//===============================
// interface INTERFACE
//
// By Simon Mitchell (96878291)
//
// Base classes: TWindow
//===============================

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
#include "biomorph.h"

#ifndef BIOVIEW
#define BIOVIEW

// The background color for the application

const int r=195;
const int g=195;
const int b=195;

class Interface : public TWindow
{

  public:

    Interface(char *);
    ~Interface();
    void Paint(TDC&, bool, TRect&);

  protected:

    TBiomorph *myMorph;
    char *myName;
};

#endif