/*======================================
TStatsDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/dialog.h>
#include <owl/scrollba.h>
#include <owl/edit.h>
#include "part_b.h"
#include "resourc2.rh"

#ifndef STATS_DIALOG
#define STATS_DIALOG

class TStatsDialog : public TDialog
{
  public:

    TStatsDialog(Interface *, TResId);
    ~TStatsDialog();

    void ShowGraph();
    void CloseWindow(){TDialog::CloseWindow();};

  protected:

    TButton *show, *ok;

    Interface *myParent;

  // Declare the response table for this class

  DECLARE_RESPONSE_TABLE(TStatsDialog);
};

#endif