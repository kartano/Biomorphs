/*======================================
TEditDialog IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include "edit.h"
#include "part_b.h"

// Response table definition

DEFINE_RESPONSE_TABLE1(TEditDialog, TDialog)
  EV_COMMAND(TBU_OK, ChangeParent),
  EV_COMMAND(TBU_RESET, Reset),
  EV_COMMAND(TBU_CANCEL, CloseWindow),
  EV_COMMAND(TBU_ZERO, ZeroValues),
  EV_COMMAND(TBU_APLUS, APlus),
  EV_COMMAND(TBU_BPLUS, BPlus),
  EV_COMMAND(TBU_CPLUS, CPlus),
  EV_COMMAND(TBU_DPLUS, DPlus),
  EV_COMMAND(TBU_EPLUS, EPlus),
  EV_COMMAND(TBU_FPLUS, FPlus),
  EV_COMMAND(TBU_GPLUS, GPlus),
  EV_COMMAND(TBU_HPLUS, HPlus),
  EV_COMMAND(TBU_IPLUS, IPlus),
  EV_COMMAND(TBU_JPLUS, JPlus),
  EV_COMMAND(TBU_KPLUS, KPlus),

  EV_COMMAND(TBU_CCPLUS, CCPlus),
  EV_COMMAND(TBU_DDPLUS, DDPlus),
  EV_COMMAND(TBU_EEPLUS, EEPlus),
  EV_COMMAND(TBU_FFPLUS, FFPlus),
  EV_COMMAND(TBU_GGPLUS, GGPlus),
  EV_COMMAND(TBU_HHPLUS, HHPlus),
  EV_COMMAND(TBU_IIPLUS, IIPlus),
  EV_COMMAND(TBU_JJPLUS, JJPlus),
  EV_COMMAND(TBU_KKPLUS, KKPlus),

  EV_COMMAND(TBU_AMINUS, AMinus),
  EV_COMMAND(TBU_BMINUS, BMinus),
  EV_COMMAND(TBU_CMINUS, CMinus),
  EV_COMMAND(TBU_DMINUS, DMinus),
  EV_COMMAND(TBU_EMINUS, EMinus),
  EV_COMMAND(TBU_FMINUS, FMinus),
  EV_COMMAND(TBU_GMINUS, GMinus),
  EV_COMMAND(TBU_HMINUS, HMinus),
  EV_COMMAND(TBU_IMINUS, IMinus),
  EV_COMMAND(TBU_JMINUS, JMinus),
  EV_COMMAND(TBU_KMINUS, KMinus),

  EV_COMMAND(TBU_CCMINUS, CCMinus),
  EV_COMMAND(TBU_DDMINUS, DDMinus),
  EV_COMMAND(TBU_EEMINUS, EEMinus),
  EV_COMMAND(TBU_FFMINUS, FFMinus),
  EV_COMMAND(TBU_GGMINUS, GGMinus),
  EV_COMMAND(TBU_HHMINUS, HHMinus),
  EV_COMMAND(TBU_IIMINUS, IIMinus),
  EV_COMMAND(TBU_JJMINUS, JJMinus),
  EV_COMMAND(TBU_KKMINUS, KKMinus),

  EV_COMMAND_ENABLE(TED_AVAL, CeAVal),
  EV_COMMAND_ENABLE(TED_BVAL, CeBVal),
  EV_COMMAND_ENABLE(TED_CVAL, CeCVal),
  EV_COMMAND_ENABLE(TED_DVAL, CeDVal),
  EV_COMMAND_ENABLE(TED_EVAL, CeEVal),
  EV_COMMAND_ENABLE(TED_FVAL, CeFVal),
  EV_COMMAND_ENABLE(TED_GVAL, CeGVal),
  EV_COMMAND_ENABLE(TED_HVAL, CeHVal),
  EV_COMMAND_ENABLE(TED_IVAL, CeIVal),
  EV_COMMAND_ENABLE(TED_JVAL, CeJVal),
  EV_COMMAND_ENABLE(TED_KVAL, CeKVal),

  EV_COMMAND_ENABLE(TBU_IPLUS, CeIPlus),
  EV_COMMAND_ENABLE(TBU_IIPLUS, CeIIPlus),
  EV_COMMAND_ENABLE(TBU_IMINUS, CeIMinus),
  EV_COMMAND_ENABLE(TBU_IIMINUS, CeIIMinus),

  EV_COMMAND_ENABLE(TBU_JPLUS, CeJPlus),
  EV_COMMAND_ENABLE(TBU_JJPLUS, CeJJPlus),
  EV_COMMAND_ENABLE(TBU_JMINUS, CeJMinus),
  EV_COMMAND_ENABLE(TBU_JJMINUS, CeJJMinus),

  EV_COMMAND_ENABLE(TBU_KPLUS, CeKPlus),
  EV_COMMAND_ENABLE(TBU_KKPLUS, CeKKPlus),
  EV_COMMAND_ENABLE(TBU_KMINUS, CeKMinus),
  EV_COMMAND_ENABLE(TBU_KKMINUS, CeKKMinus),

END_RESPONSE_TABLE;

//===================================
// CONSTRUCTOR
//===================================

TEditDialog::TEditDialog(Interface *parent, TResId id,
int &aGene,
int &bGene,
int &cGene,
int &dGene,
int &eGene,
int &fGene,
int &gGene,
int &hGene,
int &iGene,
int &jGene,
int &kGene,
bool flag):TDialog(parent, id,0)
{
  changed=false;
  myParent=parent;
  useColors=flag;
  if (!useColors)
    {
      iGene=0;
      jGene=0;
      kGene=0;
    }

  editMorph = new TBiomorph(useColors,defR, defG, defB, 80, 80);
  editMorph->SetGenes(aGene,bGene,cGene,dGene,eGene,fGene,gGene,hGene, iGene, jGene, kGene);

  oa=aGene;
  ob=bGene;
  oc=cGene;
  od=dGene;
  oe=eGene;
  of=fGene;
  og=gGene;
  oh=hGene;
  oi=iGene;
  oj=jGene;
  ok=kGene;

  parentBox = new TStatic(this,TST_EDITPARENT,"",10,10,250,220);
  parentBox->Attr.Style=(parentBox->Attr.Style | SS_ETCHEDFRAME);

  ok_ = new TButton(this,TBU_OK,"OK",10,370,110,32);
  cancel = new TButton(this,TBU_CANCEL,"CANCEL",160,370,110,32);
  reset = new TButton(this,TBU_RESET,"RESET",310,370,110,32);
  zeroValues = new TButton(this,TBU_ZERO,"ZERO VALUES",460,370,110,32);

  aplus= new TButton(this,TBU_APLUS,">",670,30,20,20);
  aminus=new TButton(this,TBU_AMINUS,"<",560,30,20,20);
  bplus= new TButton(this,TBU_BPLUS,">",670,60,20,20);
  bminus=new TButton(this,TBU_BMINUS,"<",560,60,20,20);

  cplus= new TButton(this,TBU_CPLUS,">",670,90,20,20);
  cminus=new TButton(this,TBU_CMINUS,"<",560,90,20,20);
  ccplus=new TButton(this,TBU_CCPLUS,">>",700,90,20,20);
  ccminus=new TButton(this,TBU_CCMINUS,"<<",530,90,20,20);

  dplus= new TButton(this,TBU_DPLUS,">",670,120,20,20);
  dminus=new TButton(this,TBU_DMINUS,"<",560,120,20,20);
  ddplus=new TButton(this,TBU_DDPLUS,">>",700,120,20,20);
  ddminus=new TButton(this,TBU_DDMINUS,"<<",530,120,20,20);

  eplus= new TButton(this,TBU_EPLUS,">",670,150,20,20);
  eminus=new TButton(this,TBU_EMINUS,"<",560,150,20,20);
  eeplus=new TButton(this,TBU_EEPLUS,">>",700,150,20,20);
  eeminus=new TButton(this,TBU_EEMINUS,"<<",530,150,20,20);

  fplus= new TButton(this,TBU_FPLUS,">",670,180,20,20);
  fminus=new TButton(this,TBU_FMINUS,"<",560,180,20,20);
  ffplus=new TButton(this,TBU_FFPLUS,">>",700,180,20,20);
  ffminus=new TButton(this,TBU_FFMINUS,"<<",530,180,20,20);

  gplus= new TButton(this,TBU_GPLUS,">",670,210,20,20);
  gminus=new TButton(this,TBU_GMINUS,"<",560,210,20,20);
  ggplus=new TButton(this,TBU_GGPLUS,">>",700,210,20,20);
  ggminus=new TButton(this,TBU_GGMINUS,"<<",530,210,20,20);

  hplus= new TButton(this,TBU_HPLUS,">",670,240,20,20);
  hminus=new TButton(this,TBU_HMINUS,"<",560,240,20,20);
  hhplus=new TButton(this,TBU_HHPLUS,">>",700,240,20,20);
  hhminus=new TButton(this,TBU_HHMINUS,"<<",530,240,20,20);

  iplus= new TButton(this,TBU_IPLUS,">",670,270,20,20);
  iminus=new TButton(this,TBU_IMINUS,"<",560,270,20,20);
  iiplus=new TButton(this,TBU_IIPLUS,">>",700,270,20,20);
  iiminus=new TButton(this,TBU_IIMINUS,"<<",530,270,20,20);

  jplus= new TButton(this,TBU_JPLUS,">",670,300,20,20);
  jminus=new TButton(this,TBU_JMINUS,"<",560,300,20,20);
  jjplus=new TButton(this,TBU_JJPLUS,">>",700,300,20,20);
  jjminus=new TButton(this,TBU_JJMINUS,"<<",530,300,20,20);

  kplus= new TButton(this,TBU_KPLUS,">",670,330,20,20);
  kminus=new TButton(this,TBU_KMINUS,"<",560,330,20,20);
  kkplus=new TButton(this,TBU_KKPLUS,">>",700,330,20,20);
  kkminus=new TButton(this,TBU_KKMINUS,"<<",530,330,20,20);

  aDes = new TStatic(this,TST_ADESC,"Number of offspring:",270,30,200,30);
  bDes = new TStatic(this,TST_BDESC,"Number of iterations:",270,60,200,30);
  cDes = new TStatic(this,TST_CDESC,"Length of first line:",270,90,200,30);
  dDes = new TStatic(this,TST_DDESC,"Length of second line:",270,120,200,30);
  eDes = new TStatic(this,TST_EDESC,"Offshoot point:",270,150,200,30);
  fDes = new TStatic(this,TST_FDESC,"First angle:",270,180,200,30);
  gDes = new TStatic(this,TST_GDESC,"Second angle:",270,210,200,30);
  hDes = new TStatic(this,TST_HDESC,"Length of trunk:",270,240,200,30);
  iDes = new TStatic(this,TST_IDESC,"Red colouring:",270,270,200,30);
  jDes = new TStatic(this,TST_JDESC,"Green colouring:",270,300,200,30);
  kDes = new TStatic(this,TST_KDESC,"Blue colouring:",270,330,200,30);

  aNum = new TEdit(this,TED_AVAL,"0",600,30,50,20);
  bNum = new TEdit(this,TED_BVAL,"0",600,60,50,20);
  cNum = new TEdit(this,TED_CVAL,"0",600,90,50,20);
  dNum = new TEdit(this,TED_DVAL,"0",600,120,50,20);
  eNum = new TEdit(this,TED_EVAL,"0",600,150,50,20);
  fNum = new TEdit(this,TED_FVAL,"0",600,180,50,20);
  gNum = new TEdit(this,TED_GVAL,"0",600,210,50,20);
  hNum = new TEdit(this,TED_HVAL,"0",600,240,50,20);
  iNum = new TEdit(this,TED_IVAL,"0",600,270,50,20);
  jNum = new TEdit(this,TED_JVAL,"0",600,300,50,20);
  kNum = new TEdit(this,TED_KVAL,"0",600,330,50,20);
};

//===================================
// DESTRUCTOR
//===================================

TEditDialog::~TEditDialog()
{
  delete editMorph;
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

  delete aplus;
  delete bplus;
  delete cplus;
  delete dplus;
  delete eplus;
  delete fplus;
  delete gplus;
  delete hplus;
  delete iplus;
  delete jplus;
  delete kplus;

  delete ccplus;
  delete ddplus;
  delete eeplus;
  delete ffplus;
  delete ggplus;
  delete hhplus;
  delete iiplus;
  delete jjplus;
  delete kkplus;

  delete aminus;
  delete bminus;
  delete cminus;
  delete dminus;
  delete eminus;
  delete fminus;
  delete gminus;
  delete hminus;
  delete iminus;
  delete jminus;
  delete kminus;

  delete ccminus;
  delete ddminus;
  delete eeminus;
  delete ffminus;
  delete ggminus;
  delete hhminus;
  delete iiminus;
  delete jjminus;
  delete kkminus;

  delete ok_;
  delete cancel;
  delete reset;
  delete zeroValues;
};

//===================================
// SetupWindow
//
// The standard over-ridden SetupWindow method for this class
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::SetupWindow()
{
  SetValues();
  TDialog::SetupWindow();
}

//===================================
// Paint
//
// The standard over-ridden Paint method for this class
//
// Receives: TDC object, erase flag and TRect region
//  Returns: Nothing
//===================================

void TEditDialog::Paint(TDC &pdc, bool erase, TRect rect)
{
  TDialog::Paint(pdc, erase, rect);
}

//===================================
// ZeroValues
//
// Reset all the gene values to zero in the biomorph being
// edited
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::ZeroValues()
{
  Draw(true);
  editMorph->SetGenes(1,0,0,0,0,0,0,0,0,0,0);
  Draw(false);
  SetValues();
}

//===================================
// Draw
//
// This method tells the biomorph to re-draw itself
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::Draw(bool erase)
{
  TClientDC newDc(*this);
  editMorph->Display(newDc,erase);
};

//===================================
// ChangeParent
//
// This method closes the edit dialog and stores the new
// gene values back into the parent biomorph via the
// application will called it.
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::ChangeParent()
{
  int a, b, c, d, e, f, g, h, i, j, k;
  a=editMorph->GetGene(0);
  b=editMorph->GetGene(1);
  c=editMorph->GetGene(2);
  d=editMorph->GetGene(3);
  e=editMorph->GetGene(4);
  f=editMorph->GetGene(5);
  g=editMorph->GetGene(6);
  h=editMorph->GetGene(7);
  i=editMorph->GetGene(8);
  j=editMorph->GetGene(9);
  k=editMorph->GetGene(10);

  if (changed)
    myParent->AlterGenes(a,b,c,d,e,f,g,h,i,j,k);
  TDialog::CloseWindow();
};

//===================================
// Reset
//
// Resets the biomorph being edited to its original values
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::Reset()
{
  Draw(true);
  editMorph->SetGenes(oa,ob,oc,od,oe,of,og,oh,oi,oj,ok);
  Draw(false);
  SetValues();
  changed=false;
};

//===================================
// SetValues
//
// Takes the gene values from the biomorph being edited
// and displays their values in the edit boxes.
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::SetValues()
{
  char *buffer;
  buffer=new char[10];
  buffer=itoa(editMorph->GetGene(0),buffer,10);
  CopyToEdit(aNum,buffer);

  buffer=itoa(editMorph->GetGene(1),buffer,10);
  CopyToEdit(bNum,buffer);

  buffer=itoa(editMorph->GetGene(2),buffer,10);
  CopyToEdit(cNum,buffer);

  buffer=itoa(editMorph->GetGene(3),buffer,10);
  CopyToEdit(dNum,buffer);

  buffer=itoa(editMorph->GetGene(4),buffer,10);
  CopyToEdit(eNum,buffer);

  buffer=itoa(editMorph->GetGene(5),buffer,10);
  CopyToEdit(fNum,buffer);

  buffer=itoa(editMorph->GetGene(6),buffer,10);
  CopyToEdit(gNum,buffer);

  buffer=itoa(editMorph->GetGene(7),buffer,10);
  CopyToEdit(hNum,buffer);

  buffer=itoa(editMorph->GetGene(8),buffer,10);
  CopyToEdit(iNum,buffer);

  buffer=itoa(editMorph->GetGene(9),buffer,10);
  CopyToEdit(jNum,buffer);

  buffer=itoa(editMorph->GetGene(10),buffer,10);
  CopyToEdit(kNum,buffer);
};

//===================================
// CopyToEdit
//
// Copies new text across into an edit box
//
// Receives: Point to a TEdit object, pointer to new text
//  Returns: Nothing
//===================================

void TEditDialog::CopyToEdit(TEdit *editBox, char *newText)
{
  char far *buffer;
  buffer = editBox->LockBuffer();
  strcpy(buffer, newText);
  editBox->UnlockBuffer(buffer, true);
};

//===================================
// x(x)Plus or x(x)Minus
//
// These routines are all called from the response table
// by the user clicking the gene modifier buttons.
// Each routine performs necessary error checking and
// redraws the biomorph if required.
//
// Note that XXPlus refers to a large gene addition factor
//           XPlus refers to a single gene additional (+1)
//          XXMinus refers to a large gene subtraction factor
//           XMinus refers to a single gene subtration (-1)
//
// Receives: Nothing
//  Returns: Nothing
//===================================

void TEditDialog::APlus()
{
  if (editMorph->GetGene(0)<12)
    {
      Draw(true);
      editMorph->SetGene(0,editMorph->GetGene(0)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::BPlus()
{
  if (editMorph->GetGene(1)<8)
    {
      Draw(true);
      editMorph->SetGene(1,editMorph->GetGene(1)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::CPlus()
{
  Draw(true);
  editMorph->SetGene(2,editMorph->GetGene(2)+1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::CCPlus()
{
  Draw(true);
  editMorph->SetGene(2,editMorph->GetGene(2)+10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::DPlus()
{
  Draw(true);
  editMorph->SetGene(3,editMorph->GetGene(3)+1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::DDPlus()
{
  Draw(true);
  editMorph->SetGene(3,editMorph->GetGene(3)+10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::EPlus()
{
  if (editMorph->GetGene(4)<100)
    {
      Draw(true);
      editMorph->SetGene(4,editMorph->GetGene(4)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::EEPlus()
{
  Draw(true);
  if (editMorph->GetGene(4)<91)
    editMorph->SetGene(4,editMorph->GetGene(4)+10);
  else
    editMorph->SetGene(4,100);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::FPlus()
{
  Draw(true);
  editMorph->SetGene(5,editMorph->GetGene(5)+1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::FFPlus()
{
  Draw(true);
  editMorph->SetGene(5,editMorph->GetGene(5)+10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::GPlus()
{
  Draw(true);
  editMorph->SetGene(6,editMorph->GetGene(6)+1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::GGPlus()
{
  Draw(true);
  editMorph->SetGene(6,editMorph->GetGene(6)+10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::HPlus()
{
  Draw(true);
  editMorph->SetGene(7,editMorph->GetGene(7)+1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::HHPlus()
{
  Draw(true);
  editMorph->SetGene(7,editMorph->GetGene(7)+10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::IPlus()
{
  if (editMorph->GetGene(8)<255)
    {
      Draw(true);
      editMorph->SetGene(8,editMorph->GetGene(8)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::IIPlus()
{
  Draw(true);
  if (editMorph->GetGene(8)<246)
    editMorph->SetGene(8,editMorph->GetGene(8)+10);
  else
    editMorph->SetGene(8,255);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::JPlus()
{
  if (editMorph->GetGene(9)<255)
    {
      Draw(true);
      editMorph->SetGene(9,editMorph->GetGene(9)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::JJPlus()
{
  Draw(true);
  if (editMorph->GetGene(9)<246)
    editMorph->SetGene(9,editMorph->GetGene(9)+10);
  else
    editMorph->SetGene(9,255);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::KPlus()
{
  if (editMorph->GetGene(10)<255)
    {
      Draw(true);
      editMorph->SetGene(10,editMorph->GetGene(10)+1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::KKPlus()
{
  Draw(true);
  if (editMorph->GetGene(10)<246)
    editMorph->SetGene(10,editMorph->GetGene(10)+10);
  else
    editMorph->SetGene(10,255);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::AMinus()
{
  if (editMorph->GetGene(0)>1)
    {
      Draw(true);
      editMorph->SetGene(0,editMorph->GetGene(0)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::BMinus()
{
  if (editMorph->GetGene(1)>0)
    {
      Draw(true);
      editMorph->SetGene(1,editMorph->GetGene(1)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::CMinus()
{
  if (editMorph->GetGene(2)>0)
    {
      Draw(true);
      editMorph->SetGene(2,editMorph->GetGene(2)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::CCMinus()
{
  Draw(true);
  if (editMorph->GetGene(2)>9)
    editMorph->SetGene(2,editMorph->GetGene(2)-10);
  else
    editMorph->SetGene(2,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::DMinus()
{
  if (editMorph->GetGene(3)>0)
    {
      Draw(true);
      editMorph->SetGene(3,editMorph->GetGene(3)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::DDMinus()
{
  Draw(true);
  if (editMorph->GetGene(3)>9)
    editMorph->SetGene(3,editMorph->GetGene(3)-10);
  else
    editMorph->SetGene(3,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::EMinus()
{
  if (editMorph->GetGene(4)>0)
    {
      Draw(true);
      editMorph->SetGene(4,editMorph->GetGene(4)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::EEMinus()
{
  Draw(true);
  if (editMorph->GetGene(4)>9)
    editMorph->SetGene(4,editMorph->GetGene(4)-10);
  else
    editMorph->SetGene(4,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::FMinus()
{
  Draw(true);
  editMorph->SetGene(5,editMorph->GetGene(5)-1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::FFMinus()
{
  Draw(true);
  editMorph->SetGene(5,editMorph->GetGene(5)-10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::GMinus()
{
  Draw(true);
  editMorph->SetGene(6,editMorph->GetGene(6)-1);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::GGMinus()
{
  Draw(true);
  editMorph->SetGene(6,editMorph->GetGene(6)-10);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::HMinus()
{
  if (editMorph->GetGene(7)>0)
    {
      Draw(true);
      editMorph->SetGene(7,editMorph->GetGene(7)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::HHMinus()
{
  Draw(true);
  if (editMorph->GetGene(7)>9)
    editMorph->SetGene(7,editMorph->GetGene(7)-10);
  else
    editMorph->SetGene(7,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::IMinus()
{
  if (editMorph->GetGene(8)>0)
    {
      Draw(true);
      editMorph->SetGene(8,editMorph->GetGene(8)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::IIMinus()
{
  Draw(true);
  if (editMorph->GetGene(8)>9)
    editMorph->SetGene(8,editMorph->GetGene(8)-10);
  else
    editMorph->SetGene(8,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::JMinus()
{
  if (editMorph->GetGene(9)>0)
    {
      Draw(true);
      editMorph->SetGene(9,editMorph->GetGene(9)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::JJMinus()
{
  Draw(true);
  if (editMorph->GetGene(9)>9)
    editMorph->SetGene(9,editMorph->GetGene(9)-10);
  else
    editMorph->SetGene(9,0);
  SetValues();
  Draw(false);
  changed=true;
}

void TEditDialog::KMinus()
{
  if (editMorph->GetGene(10)>0)
    {
      Draw(true);
      editMorph->SetGene(10,editMorph->GetGene(10)-1);
      SetValues();
      Draw(false);
      changed=true;
    }
}

void TEditDialog::KKMinus()
{
  Draw(true);
  if (editMorph->GetGene(10)>9)
    editMorph->SetGene(10,editMorph->GetGene(10)-10);
  else
    editMorph->SetGene(10,0);
  SetValues();
  Draw(false);
  changed=true;
}

