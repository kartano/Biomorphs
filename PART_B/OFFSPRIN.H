/*======================================
TOffspringDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/dialog.h>
#include <owl/scrollba.h>
#include <owl/edit.h>
#include <owl/button.h>
#include "resourc2.rh"
#include "part_b.h"

#ifndef OFFSPRING_DIALOG
#define OFFSPRING_DIALOG

class TOffspringDialog : public TDialog

{
  public:

    TOffspringDialog(Interface *, TResId);
    ~TOffspringDialog();
    void CloseWindow();

  protected:

    TButton *ok;

    TStatic *b1, *b2, *b3, *b4, *b5, *b6, *b7, *b8, *b9, *b10, *b11, *b12;
    TStatic *aNum, *bNum, *cNum, *dNum, *eNum, *fNum, *gNum, *hNum, *iNum, *jNum, *kNum, *lNum;

  // Declare the response table for this class

  DECLARE_RESPONSE_TABLE(TOffspringDialog);
};
#endif
