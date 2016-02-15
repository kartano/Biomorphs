/*======================================
TGenesDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/dialog.h>
#include <owl/scrollba.h>
#include <owl/edit.h>
#include <owl/button.h>
#include "resourc2.rh"
#include "part_b.h"

#ifndef GENE_VALUES_DIALOG
#define GENE_VALUES_DIALOG

class TGenesDialog : public TDialog

{
  public:

    TGenesDialog(Interface *, TResId,int,int,int,int,int,int,int,int,int,int,int);
    ~TGenesDialog();
    void CloseWindow();
    void CeEnable(TCommandEnabler&);

  protected:

    TButton *ok;

    TStatic *border;

    TEdit *aNum, *bNum, *cNum, *dNum, *eNum, *fNum, *gNum, *hNum, *iNum, *jNum, *kNum;
    TStatic *aDes, *bDes, *cDes, *dDes, *eDes, *fDes, *gDes, *hDes, *iDes, *jDes, *kDes;

  // Declare the response table for this class

  DECLARE_RESPONSE_TABLE(TGenesDialog);
};

#endif