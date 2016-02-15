/*======================================

Interface IMPLEMENTATION

By Simon Mitchell (96878291)

Defines the interface for the application

BASE CLASSES: TWindow
======================================*/
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/opensave.h>
#include <stdlib.h>
#include "part_a.rc"
#include "editexam.h"
#include "setupdia.h"
#include "resource.rh"
#include "part_a.h"
#include "evolve.h"
#include "repdia.h"

// The response table

DEFINE_RESPONSE_TABLE1(Interface, TWindow)
  EV_COMMAND(ID_EVOLVEBUTTON, StartEvolution),
  EV_COMMAND(ID_SHOWREPORT, ShowReport),
  EV_COMMAND(CM_FILEOPEN, OpenFile),
  EV_COMMAND(CM_ABOUT,AboutProgram),
  EV_COMMAND(CM_SETUP, GetSettings),
END_RESPONSE_TABLE;

//------------------------------------------
// CONSTRUCTOR
//------------------------------------------

Interface::Interface():TWindow(0, 0, 0)
{
  Attr.X=110;
  Attr.Y=110;
  Attr.W=700;
  Attr.H=440;

  canShowReport=false;
  
  evoManager = new EvolutionManager();

  stepNumber=1;
  delayTime=1;
  generationLimit=100;
  showAllDetails=true;
  noDelay=true;
  limit=false;
  stepState=false;

  SetBkgndColor(TColor(164,164,164));
  editOri = new TExampleEdit(this, ID_EDIT1, "", 20, 20, 655, 168);
  new TButton (this, ID_EVOLVEBUTTON, "EVOLVE", 190,200,136,32,false);
  report = new TButton (this, ID_SHOWREPORT, "REPORT", 350,200,136,32,false);
  editEvo = new TExampleEdit(this, ID_EDIT2, "", 20, 248, 655, 168);
  FileData.SetFilter("Text files (*.TXT)|*.TXT|AllFiles (*.*)|*.*|");
}

//------------------------------------------
//  SetupWindow
//
// Sets up all the controls in this window
//
// Receives: Nothing
//  Returns: Nothing
//------------------------------------------

void Interface::SetupWindow()
{
  TWindow::SetupWindow();
  editOri->SetReadOnly(false);
  editEvo->SetReadOnly(true);
}

//------------------------------------------
//  StartEvolution
//
//  Starts the evolution process
//
// Receives: Nothing
//  Returns: Nothing
//------------------------------------------

void Interface::StartEvolution()
{
  evoManager->evolveText
    (editOri,
     editEvo,
     delayTime,
     generationLimit,
     noDelay,
     showAllDetails,
     limit);
  bool Incomplete;
  Incomplete=true;
  int currentStep=0;

  // Use this algorithm if we have an active step value ...

  if (stepState==true)
    {
      while(Incomplete)
        {
          Incomplete=evoManager->evolveTheText();
          canShowReport=true;
          SendMessage(WM_PAINT);
          currentStep++;
          if(currentStep==stepNumber)
            {
              currentStep=0;
              if (MessageBox("Step complete","Step complete",MB_OKCANCEL | MB_ICONINFORMATION)==IDCANCEL)
                Incomplete=false;
            }
        }
    }

  // .. otherwise the user did not choose the "step" option
  // so we can evolve normally.

  else
    {
      while (Incomplete)
        {
          Incomplete=evoManager->evolveTheText();
          canShowReport=true;
        }
    }
  evoManager->Finish();
}

//------------------------------------------
//  ShowReport
//
//  Displays the evolution report
//
// Receives: Nothing
//  Returns: Nothing
//------------------------------------------

void Interface::ShowReport()
{
  if (canShowReport)
    {
      evoManager->getStats(seconds, generations, maxchanges, minchanges);
      TReportDialog reportDialog(this, IDD_DIALOG3, generations, seconds, maxchanges, minchanges);
      reportDialog.Execute();
    }
  else
    MessageBox("You must have stepped or completed evolution to see a report!","Report",MB_OK|MB_ICONEXCLAMATION);
};

//------------------------------------------
// AboutProgram
//
// Display an "ABOUT" dialog box
//
// Receives: Nothing
//  Returns: Nothing
//------------------------------------------

void Interface::AboutProgram()
{
  TDialog aboutThis(this, IDD_DIALOG2);
  aboutThis.Execute();
}

//------------------------------------------
// GetSettings
//
// Display a setup dialog
//
// Receives: Nothing
//  Returns: Nothing
//------------------------------------------

void Interface::GetSettings()
{
  TSetupDialog settingsDialog(this, IDD_DIALOG4);
  settingsDialog.Execute();
}

//------------------------------------------
// Settings
//
// Accepts settings, assumedly from the setup dialog box
//
// Receives: delay time,
//           generation limit,
//           step number,
//           noDelay state,
//           detail state,
//           generation limit state,
//           step state
//  Returns: Nothing
//------------------------------------------

void Interface::Settings(int newTime, int newGenLimit, int newStepNumber,
     bool noDelState, bool detailState, bool limitState, bool newStepState)
{
  stepNumber=newStepNumber;
  delayTime=newTime;
  generationLimit=newGenLimit;
  showAllDetails=detailState;
  noDelay=noDelState;
  limit=limitState;
  stepState=newStepState;
}

/*======================================

InterfaceApp IMPLEMENTATION

By Simon Mitchell (96878291)

  Creates a thread for this application and assigns a
display to it.

BASE CLASSES: TApplication
======================================*/

class InterfaceApp : public TApplication
{
  public:

    InterfaceApp() : TApplication() {}
    void InitMainWindow()
  {
    Interface *myInterface = new Interface ();
    TFrameWindow *myFrame =
      new TFrameWindow(0,"Text evolution program",myInterface,true);
    myFrame->Attr.Style &= ~WS_THICKFRAME;
    SetMainWindow(myFrame);
    GetMainWindow()->AssignMenu("COMMANDS");
  }
};
//======================================
// MAIN LINE
//======================================

int OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return InterfaceApp().Run();
}

