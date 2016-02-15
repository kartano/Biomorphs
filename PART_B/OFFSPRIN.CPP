/*======================================
TOffspringDialog IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include "offsprin.h"

DEFINE_RESPONSE_TABLE1(TOffspringDialog, TDialog)
  EV_COMMAND(TBU_OK4, CloseWindow),
END_RESPONSE_TABLE;

//===================================
// CONSTRUCTOR
//===================================

TOffspringDialog::TOffspringDialog(Interface *parent, TResId id):TDialog(parent,id)
{
  char *buffer;
  buffer = new char[10];

  b1 = new TStatic(this,TST_BOX_1,"",10,10,60,60);
  b1->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(0),buffer,10);
  aNum = new TStatic(this,TST_VAL1,buffer,20,30,40,20);
  b2 = new TStatic(this,TST_BOX_2,"",80,10,60,60);
  b2->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(1),buffer,10);
  bNum = new TStatic(this,TST_VAL2,buffer,90,30,40,20);
  b3 = new TStatic(this,TST_BOX_3,"",150,10,60,60);
  b3->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(2),buffer,10);
  cNum = new TStatic(this,TST_VAL3,buffer,160,30,40,20);
  b4 = new TStatic(this,TST_BOX_4,"",220,10,60,60);
  b4->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(3),buffer,10);
  dNum = new TStatic(this,TST_VAL4,buffer,230,30,40,20);

  b5 = new TStatic(this,TST_BOX_5,"",10,80,60,60);
  b5->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(4),buffer,10);
  eNum = new TStatic(this,TST_VAL5,buffer,20,100,40,20);
  b6 = new TStatic(this,TST_BOX_6,"",220,80,60,60);
  b6->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(5),buffer,10);
  fNum = new TStatic(this,TST_VAL6,buffer,230,100,40,20);

  b7 = new TStatic(this,TST_BOX_7,"",10,150,60,60);
  b7->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(6),buffer,10);
  gNum = new TStatic(this,TST_VAL7,buffer,20,170,40,20);
  b8 = new TStatic(this,TST_BOX_8,"",220,150,60,60);
  b8->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(7),buffer,10);
  hNum = new TStatic(this,TST_VAL8,buffer,230,170,40,20);

  b9 = new TStatic(this,TST_BOX_9,"",10,220,60,60);
  b9->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(8),buffer,10);
  iNum = new TStatic(this,TST_VAL9,buffer,20,240,40,20);
  b10 = new TStatic(this,TST_BOX_10,"",80,220,60,60);
  b10->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(9),buffer,10);
  jNum = new TStatic(this,TST_VAL10,buffer,90,240,40,20);
  b11 = new TStatic(this,TST_BOX_11,"",150,220,60,60);
  b11->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(10),buffer,10);
  kNum = new TStatic(this,TST_VAL11,buffer,160,240,40,20);
  b12 = new TStatic(this,TST_BOX_12,"",220,220,60,60);
  b12->Attr.Style|=SS_ETCHEDFRAME;
  buffer=itoa(parent->GetBoxCount(11),buffer,10);
  lNum = new TStatic(this,TST_VAL12,buffer,230,240,40,20);

  ok = new TButton(this,TBU_OK4,"OK",100,130,96,36);
}

//===================================
// DESTRUCTOR
//===================================

TOffspringDialog::~TOffspringDialog()
{
  delete ok;
  delete b1;
  delete b2;
  delete b3;
  delete b4;
  delete b5;
  delete b6;
  delete b7;
  delete b8;
  delete b9;
  delete b10;
  delete b11;
  delete b12;
  delete aNum;
  delete bNum;
  delete cNum;
  delete dNum;
  delete eNum;
  delete fNum;
  delete gNum;
  delete hNum;
  delete iNum;
  delete jNum;
  delete kNum;
  delete lNum;
}

//===================================
// CloseWindow
//
// The standard over-ridden CloseWindow method for this class
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TOffspringDialog::CloseWindow()
{
  TDialog::CloseWindow();
}
