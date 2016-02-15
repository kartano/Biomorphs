/*======================================

TSetupDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/
#ifndef SETUP_DIALOG_CLASS
#define SETUP_DIALOG_CLASS

#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/edit.h>

#include "resource.rh"
#include "part_a.h"

class TSetupDialog : public TDialog
{
  public:

    TSetupDialog(Interface *parent, TResId id);

  protected:

    void CeDelayTime (TCommandEnabler&);
    void CeGenerations (TCommandEnabler&);
    void CeStepNumber (TCommandEnabler&);
    void CloseWindow ();
    void TransferData ();
    void SetupWindow();
    bool CanClose();

    // GUI elements

    TGroupBox *evoOptions, *delayOptions, *stepOptions;
    TRadioButton *evoToEnd, *evoToLimit, *noDel, *userDefDel, *noStep, *step;
    TEdit *delayTime, *generations, *stepNumber;
    TCheckBox *showAll;
    TButton *finished;

  private:

    // Pointer to parent

    Interface *theParent;

    // Response table declaration

    DECLARE_RESPONSE_TABLE(TSetupDialog);
};

#endif