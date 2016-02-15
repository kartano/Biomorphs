/*======================================

TReportDialog IMPLEMENTATION

By Simon Mitchell (96878291)

  TReportDialog displays an evolution report based on
information contained withing its application class.

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
#include <owl/opensave.h>
#include <fstream.h>
#include <stdlib.h>

#include "repdia.h"

// RESPONSE TABLE ENTRIES

DEFINE_RESPONSE_TABLE1(TReportDialog,TDialog)
  EV_COMMAND(ID_EXITREPORT, CloseWindow),
  EV_COMMAND(ID_SAVEREPORT, SaveReport),
END_RESPONSE_TABLE;

//-------------------------------------
// CONSTRUCTOR
//-------------------------------------

TReportDialog::TReportDialog
  (Interface *parent,
   TResId id,
   int generations,
   int seconds,
   int maxChange,
   int minChange)
   :TDialog(parent,id,0)
{
  theParent=parent;
  theTitle = new TStatic(this,ID_REPORT,"EVOLUTION REPORT",160,15,200,32);
  theTitle->Attr.Style=(theTitle->Attr.Style | SS_CENTER);

  genTitle = new TStatic(this,ID_GENTITLE,"Generations taken.",110,50,370,32);
  genTitle->Attr.Style=(genTitle->Attr.Style | SS_LEFT);

  secTitle = new TStatic(this,ID_SECTITLE,"Seconds taken.",110,90,370,32);
  secTitle->Attr.Style=(secTitle->Attr.Style | SS_LEFT);

  maxTitle = new TStatic(this,ID_MAXTITLE,"Maximum changes per generation.",110,130,370,32);
  maxTitle->Attr.Style=(maxTitle->Attr.Style | SS_LEFT);

  minTitle = new TStatic(this,ID_MINTITLE,"Minimum changes per generation.",110,170,370,32);
  minTitle->Attr.Style=(minTitle->Attr.Style | SS_LEFT);

  char *buffer;
  buffer = new char[20];

  buffer=itoa(generations,buffer,10);
  numGens = new TStatic(this,ID_GENS, buffer,50,50,50,20);
  numGens->Attr.Style=(numGens->Attr.Style | WS_BORDER | SS_LEFT);

  buffer=itoa(seconds,buffer,10);
  numSeconds = new TStatic(this,ID_GENS, buffer,50,90,50,20);
  numSeconds->Attr.Style=(numSeconds->Attr.Style | WS_BORDER | SS_LEFT);

  buffer=itoa(maxChange,buffer,10);
  numMax = new TStatic(this,ID_MAX,buffer,50,130,50,20);
  numMax->Attr.Style=(numMax->Attr.Style | WS_BORDER | WS_VISIBLE | SS_LEFT);

  buffer=itoa(minChange,buffer,10);
  numMin = new TStatic(this,ID_MIN,buffer,50,170,50,20);
  numMin->Attr.Style=(numMin->Attr.Style | WS_BORDER | SS_LEFT);

  if (parent->GetNoDelState())
    buffer="No delay used between generations.";
  else
    {
      buffer=itoa(parent->GetDelayTime(),buffer,10);
      delayTime = new TStatic(this,ID_DELAYVAL,buffer,50,240,50,20);
      delayTime->Attr.Style=(delayTime->Attr.Style | WS_BORDER | SS_LEFT);
      buffer="A delay between generations was used.";
    }
  delTitle = new TStatic(this,ID_DELAYTITLE,buffer,120,240,290,20);
  delTitle->Attr.Style=(delTitle->Attr.Style | SS_LEFT);

  if (parent->GetLimitState())
    {
      buffer=itoa(parent->GetGenLimit(),buffer,10);
      limitNumber = new TStatic(this,ID_LIMIT,buffer,50,270,50,20);
      limitNumber->Attr.Style=(limitNumber->Attr.Style | WS_BORDER | SS_LEFT);
      buffer="A generation limit was set.";
    }
  else
    buffer="No generation limit was set.";
  limitTitle = new TStatic(this,ID_LIMITTITLE,buffer,120,270,290,20);
  limitTitle->Attr.Style=(limitTitle->Attr.Style | SS_LEFT);

  if (parent->GetDetailState())
    buffer="All generations were shown.";
  else
    buffer="Only the final generation was displayed.";
  showAllTitle = new TStatic(this,ID_SHOWNALL,buffer,120,300,290,20);
  showAllTitle->Attr.Style=(showAllTitle->Attr.Style | SS_LEFT);

  saveReport = new TButton(this,ID_SAVEREPORT,"Save",410,240,80,32,false);
  exitReport = new TButton(this,ID_EXITREPORT,"Exit",410,280,80,32,false);

  FileData.Flags = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
  FileData.SetFilter("Report files (*.OUT)|*.OUT|AllFiles (*.*)|*.*|");
}

//-------------------------------------
// SaveReport
//
// Saves the report to an .out file on disk
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TReportDialog::SaveReport()
{
  if (TFileSaveDialog(GetApplication()->MainWindow, FileData).Execute() == IDOK)
    {
      ofstream ofs(FileData.FileName, ios::out);
      ofs << "EVOLUTION REPORT!\n";
      ofs << "--------- -------\n\n";
      ofs << "             Generations taken: " << theParent->GetGenerations() << "\n";
      ofs << "                 Seconds taken: " << theParent->GetSeconds() << "\n";
      ofs << "Maximum changes per generation: " << theParent->GetMaxChanges() << "\n";
      ofs << "Minimum changes per generation: " << theParent->GetMinChanges() << "\n\n";
      ofs << "EVOLUTION SETTINGS:\n";
      ofs << "--------- -------- \n\n";
      if (theParent->GetNoDelState())
        ofs << "No delay time was used.\n";
      else
        {
          ofs << "A delay time of " << theParent->GetDelayTime();
          (theParent->GetDelayTime()==1) ? ofs << " second.\n" : ofs << " seconds.\n";
        }

      if (theParent->GetLimitState())
        {
          ofs << "A generation limit of " << theParent->GetGenLimit();
          (theParent->GetGenLimit()==1) ? ofs << " generation was used.\n" : ofs << " generations was used.\n";
        }
      else
        ofs << "No generation limit was imposed.\n";

      if (theParent->GetDetailState())
        ofs << "All generations were shown.\n";
      else
        ofs << "Only the final generation was displayed.\n";
      ofs.close();
    }
};

//-------------------------------------
// CloseWindow
//
// This method is the standard over-ridden CloseWindow method for the dialog
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TReportDialog::CloseWindow()
{
  TDialog::CloseWindow();
};

