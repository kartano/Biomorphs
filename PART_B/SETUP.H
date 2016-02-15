/*======================================
TSetupDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/dialog.h>
#include <owl/pch.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include "resourc2.rh"

#ifndef SETUP_DIALOG
#define SETUP_DIALOG

#include "part_b.h"

class TSetupDialog : public TDialog
{

  public:

    TSetupDialog(Interface *, TResId);
    ~TSetupDialog();
    void CloseWindow();
    void SetupWindow();

  private:

    // Interface elements

    TButton *ok, *cancel;


    TGroupBox *animationGroup;
    TRadioButton *animationOn, *animationOff;

  protected:

  DECLARE_RESPONSE_TABLE(TSetupDialog);

};

#endif
