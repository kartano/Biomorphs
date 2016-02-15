/*======================================

TSetupDialog IMPLEMENTATION

By Simon Mitchell (96878291)

  TSetupDialog creates a settings dialog box.

BASE CLASSES: TDialog

======================================*/
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/validate.h>
#include <stdlib.h>

#include "setupdia.h"

// Response table entries

DEFINE_RESPONSE_TABLE1(TSetupDialog,TDialog)
  EV_COMMAND_ENABLE(ID_DELAYTIME, CeDelayTime),
  EV_COMMAND_ENABLE(ID_GENERATIONS, CeGenerations),
  EV_COMMAND_ENABLE(ID_STEPNUMBER, CeStepNumber),
  EV_COMMAND(ID_FINISHED, CloseWindow),
END_RESPONSE_TABLE;

//-------------------------------------
// CONSTRUCTOR
//-------------------------------------

TSetupDialog::TSetupDialog(Interface *parent, TResId id):TDialog(parent,id,0)
{
  theParent=parent;
  char *buffer;
  buffer = new char[10];
  evoOptions = new TGroupBox(this, ID_GROUPBOX1, "Evolution options", 15, 0, 350, 82);
  evoToEnd = new TRadioButton(this, ID_RBUTTON1, "Evolve to end",30, 20, 138, 24, evoOptions);
  evoToLimit = new TRadioButton(this, ID_RBUTTON2, "Evolve to limit",30, 50, 130, 24, evoOptions);
  delayOptions = new TGroupBox(this, ID_GROUPBOX2, "Delay options", 15, 100, 350, 82);
  noDel = new TRadioButton(this, ID_RBUTTON3, "No delay",30, 120, 138, 24, delayOptions);
  userDefDel = new TRadioButton(this, ID_RBUTTON4, "Delay time",30, 150, 100, 24, delayOptions);
  buffer=itoa(theParent->GetGenLimit(),buffer,10);
  generations = new TEdit(this, ID_GENERATIONS, buffer, 165, 50, 80, 24, 10,false);

  buffer=itoa(theParent->GetDelayTime(),buffer,10);
  delayTime = new TEdit(this, ID_DELAYTIME, buffer, 165, 150, 80, 24, 10,false);

  stepOptions = new TGroupBox(this, ID_STEPBOX, "Step options", 15, 200, 350, 82);
  noStep = new TRadioButton(this, ID_NOSTEP, "No stepping",30, 220, 138, 24, stepOptions);
  step = new TRadioButton(this, ID_STEP, "Step",30, 250, 130, 24, stepOptions);
  buffer=itoa(theParent->GetStepNumber(),buffer,10);
  stepNumber = new TEdit(this, ID_STEPNUMBER, buffer, 165, 250, 80, 24, 10,false);

  showAll = new TCheckBox(this, ID_SHOWALL,"Display text during evolution",60,300,250,32);
  finished = new TButton (this, ID_FINISHED,"OK",150,340,64,32,true);
};

//-------------------------------------
// SetupWindow
//
// Sets all the controls for the dialog
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::SetupWindow()
{
  TDialog::SetupWindow();
  if (theParent->GetNoDelState())
    noDel->Check();
  else
    userDefDel->Check();
  if (theParent->GetDetailState())
    showAll->Check();
  if (theParent->GetLimitState())
    evoToLimit->Check();
  else
    evoToEnd->Check();
  if (theParent->GetStepState())
    step->Check();
  else
    noStep->Check();
}

//-------------------------------------
// CeDelayTime
//
// Uses a command enabler to turn on/off the delay time edit
// box, depending on whether a delay time was selected.
//
// Receives: Command enabler
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::CeDelayTime(TCommandEnabler& ce)
{
  ce.Enable(userDefDel->GetCheck() == BF_CHECKED ? true : false);
}

//-------------------------------------
// CeGenerations
//
// Uses a command enabler to turn on/off the generation limit
// box, depending on whether a generation limit was selected.
//
// Receives: Command enabler
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::CeGenerations(TCommandEnabler& ce)
{
  ce.Enable(evoToLimit->GetCheck() == BF_CHECKED ? true : false);
}

//-------------------------------------
// CeStepNumber
//
// Uses a command enabler to turn on/off the step number
// box, depending on whether step was selected.
//
// Receives: Command enabler
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::CeStepNumber(TCommandEnabler& ce)
{
  ce.Enable(step->GetCheck() == BF_CHECKED ? true : false);
}

//-------------------------------------
// CloseWindow
//
// Calls TDialog CloseWindow to destroy this instance
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::CloseWindow()
{
  TransferData();
  TDialog::CloseWindow();
}

//-------------------------------------
// CanClose
//
// Determins if this dialog can be closed or not.
// This method performs some basic range checking.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

bool TSetupDialog::CanClose()
{
  bool canClose = true;
  char far *buffer;
  int testVar;
  buffer = generations->LockBuffer(10);
  testVar=atoi(buffer);
  generations->UnlockBuffer(buffer);

  // Test the range of the generation limit value
  // if a generation limit is being set by the user

  if (evoToLimit->GetCheck() == BF_CHECKED)
    {
      if ((testVar<1)||(testVar>9999))
        {
          MessageBox("You must enter a generation limit between 1 and 9999","Generation limit range error",MB_OK | MB_ICONEXCLAMATION);
          canClose=false;
        }
    }
  buffer = stepNumber->LockBuffer(10);
  testVar=atoi(buffer);
  stepNumber->UnlockBuffer(buffer);

  // Check the range of the "step number" value
  // if the user has selected the STEP option

  if (step->GetCheck() == BF_CHECKED)
    {
      if ((testVar<1)||(testVar>9999))
        {
          MessageBox("You must enter a step number between 1 and 9999","Step number range error",MB_OK | MB_ICONEXCLAMATION);
          canClose=false;
        }
    }
  buffer = delayTime->LockBuffer(10);
  testVar=atoi(buffer);
  delayTime->UnlockBuffer(buffer);

  // Test the range of the delay time value
  // if the user has selected a delay time option

  if (userDefDel->GetCheck() == BF_CHECKED)
    {
      if ((testVar<1)||(testVar>9999))
        {
          MessageBox("You must enter a delay time between 1 and 9999","Delay time range error",MB_OK | MB_ICONEXCLAMATION);
          canClose=false;
        }
    }
    
  return canClose;
}

//-------------------------------------
// TransferData
//
// Transfers data from setup to the parent process
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TSetupDialog::TransferData()
{
  bool noGenLimit = evoToLimit->GetCheck();
  bool noDelay = noDel->GetCheck();
  bool showAllGens = showAll->GetCheck();
  bool stepState = step->GetCheck();
  char far *buffer;
  buffer = generations->LockBuffer(10);
  int genLimit=atoi(buffer);
  generations->UnlockBuffer(buffer);
  buffer = delayTime->LockBuffer(10);
  int delayInt=atoi(buffer);
  delayTime->UnlockBuffer(buffer);
  buffer=stepNumber->LockBuffer(10);
  int stepNum=atoi(buffer);
  stepNumber->UnlockBuffer(buffer);
  theParent->Settings(delayInt,genLimit,stepNum,noDelay,showAllGens,noGenLimit, stepState);
}

