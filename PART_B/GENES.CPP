/*======================================
TGenesDialog IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include "genes.h"

DEFINE_RESPONSE_TABLE1(TGenesDialog, TDialog)
  EV_COMMAND(TBU_OK3, CloseWindow),
  EV_COMMAND_ENABLE(TED_AVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_BVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_CVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_DVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_EVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_FVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_GVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_HVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_IVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_JVAL2, CeEnable),
  EV_COMMAND_ENABLE(TED_KVAL2, CeEnable),
END_RESPONSE_TABLE;

//===================================
// CONSTRUCTOR
//===================================

TGenesDialog::TGenesDialog(Interface *parent, TResId id,
int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k):TDialog(parent,id)
{

  border = new TStatic(this,TST_BORDER,"",10,10,325,395);
  border->Attr.Style|=SS_ETCHEDFRAME;

  ok = new TButton (this, TBU_OK3, "OK",125,365,96,32);

  aDes = new TStatic(this,TST_ADESC2,"Number of offspring:",30,30,200,20);
  bDes = new TStatic(this,TST_BDESC2,"Number of iterations:",30,60,200,20);
  cDes = new TStatic(this,TST_CDESC2,"Length of first line:",30,90,200,20);
  dDes = new TStatic(this,TST_DDESC2,"Length of second line:",30,120,200,20);
  eDes = new TStatic(this,TST_EDESC2,"Offshoot point:",30,150,200,20);
  fDes = new TStatic(this,TST_FDESC2,"First angle:",30,180,200,20);
  gDes = new TStatic(this,TST_GDESC2,"Second angle:",30,210,200,20);
  hDes = new TStatic(this,TST_HDESC2,"Length of trunk:",30,240,200,20);
  iDes = new TStatic(this,TST_IDESC2,"Red colour element:",30,270,200,20);
  jDes = new TStatic(this,TST_JDESC2,"Green colour element:",30,300,200,20);
  kDes = new TStatic(this,TST_KDESC2,"Blue colour element:",30,330,200,20);

  char *buffer;
  buffer = new char[10];
  buffer=itoa(a,buffer,10);
  aNum = new TEdit(this,TED_AVAL2,buffer,260,30,60,20);
  buffer=itoa(b,buffer,10);
  bNum = new TEdit(this,TED_BVAL2,buffer,260,60,60,20);
  buffer=itoa(c,buffer,10);
  cNum = new TEdit(this,TED_CVAL2,buffer,260,90,60,20);
  buffer=itoa(d,buffer,10);
  dNum = new TEdit(this,TED_DVAL2,buffer,260,120,60,20);
  buffer=itoa(e,buffer,10);
  eNum = new TEdit(this,TED_EVAL2,buffer,260,150,60,20);
  buffer=itoa(f,buffer,10);
  fNum = new TEdit(this,TED_FVAL2,buffer,260,180,60,20);
  buffer=itoa(g,buffer,10);
  gNum = new TEdit(this,TED_GVAL2,buffer,260,210,60,20);
  buffer=itoa(h,buffer,10);
  hNum = new TEdit(this,TED_HVAL2,buffer,260,240,60,20);
  buffer=itoa(i,buffer,10);
  iNum = new TEdit(this,TED_IVAL2,buffer,260,270,60,20);
  buffer=itoa(j,buffer,10);
  jNum = new TEdit(this,TED_JVAL2,buffer,260,300,60,20);
  buffer=itoa(k,buffer,10);
  kNum = new TEdit(this,TED_KVAL2,buffer,260,330,60,20);
};

//===================================
// DESTRUCTOR
//===================================

TGenesDialog::~TGenesDialog()
{
  delete ok;
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
  delete aDes;
  delete bDes;
  delete cDes;
  delete dDes;
  delete eDes;
  delete fDes;
  delete gDes;
  delete hDes;
  delete iDes;
  delete jDes;
  delete kDes;
  delete border;
}

//===================================
// CloseWindow
//
// The standard over-ridden CloseWindow method for this class
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TGenesDialog::CloseWindow()
{
  TDialog::CloseWindow();
};

//===================================
// CeEnable
//
// Standard method to make sure all edit boxes are disabled.
//
// Receives: Address of a TCommandEnabler object
//  Returns: Nothing
//===================================

void TGenesDialog::CeEnable(TCommandEnabler &ce)
{
  ce.Enable(false);
};

