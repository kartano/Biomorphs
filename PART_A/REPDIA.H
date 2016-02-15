/*======================================

TReportDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#ifndef REPORT_DIALOG_CLASS
#define REPORT_DIALOG_CLASS

#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/edit.h>
#include <owl/button.h>
#include <owl/opensave.h>
#include <fstream.h>

#include "resource.rh"
#include "part_a.h"

class TReportDialog : public TDialog
{
  public:

    TReportDialog(Interface*, TResId,int,int,int,int);
    void CloseWindow();

  protected:

  private:

    void SaveReport();

    Interface *theParent;

    // Interface elements

    TStatic *theTitle, *numGens,  *numSeconds, *numMax, *numMin;
    TStatic *delayTime, *limitNumber;
    TStatic *genTitle, *secTitle, *maxTitle, *minTitle;
    TStatic *delTitle, *limitTitle, *showAllTitle;
    TButton *saveReport, *exitReport;
    TOpenSaveDialog::TData  FileData;

    // Response table declaration

    DECLARE_RESPONSE_TABLE(TReportDialog);
};

#endif