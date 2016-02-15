/*======================================
TSetupDialog IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/uihelper.h>
#include "setup.h"

// Response table definition

DEFINE_RESPONSE_TABLE1(TSetupDialog, TDialog)
  EV_COMMAND(TBU_OK2, CloseWindow),
  EV_COMMAND(TBU_CANCEL2, CloseWindow),
END_RESPONSE_TABLE;

//======================================
// CONSTRUCTOR
//======================================

TSetupDialog::TSetupDialog(Interface *parent, TResId id):TDialog(parent, id, 0)
{
  ok = new TButton(this,TBU_OK2,"OK",10,10,96,32);
  cancel = new TButton(this, TBU_CANCEL2, "CANCEL",100,10,96,32);
  animationGroup = new TGroupBox(this,TGB_ANIM,"Record animation",10,50,202,202);
  animationOn = new TRadioButton(this, TRB_ANIMON, "On",20,72,96,20,animationGroup);
  animationOff = new TRadioButton(this, TRB_ANIMOFF, "Off",20,92,96,20,animationGroup);
}

//======================================
// DESTRUCTOR
//======================================

TSetupDialog::~TSetupDialog()
{
  delete ok;
  delete cancel;
  delete animationOn;
  delete animationOff;
  delete animationGroup;
}

//======================================
// SetupWindow
//
// Standard overidden SetupWindow method. It sets up interface elements.
//
// Receives: Nothing
//  Returns: Nothing
//======================================

void TSetupDialog::SetupWindow()
{
  animationOn->Check();
};

//======================================
// CloseWindow
//
// Standard overidden CloseWindow method
//
// Receives: Nothing
//  Returns: Nothing
//======================================

void TSetupDialog::CloseWindow()
{
  MessageBox("WHAT IN THE NAME OF FUCK","FUCK",MB_OK|MB_ICONEXCLAMATION);
  TDialog::CloseWindow();
}
