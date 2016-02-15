#include <owl/uihelper.h>
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/static.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "biotest.h"

const int R=128;
const int G=128;
const int B=128;

const uint16 TSB_ITERATIONS=101;
const uint16 TSB_BRLEN1=102;
const uint16 TSB_BRLEN2=103;
const uint16 TSB_COMBINE=104;
const uint16 TSB_ANG1=105;
const uint16 TSB_ANG2=106;
const uint16 TSB_TRUNK=107;

const float M_2PI = M_PI * 2;

DEFINE_RESPONSE_TABLE1(Interface, TWindow)
  EV_CHILD_NOTIFY_ALL_CODES(TSB_ITERATIONS, EvAChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_BRLEN1, EvBChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_BRLEN2, EvCChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_COMBINE, EvDChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_ANG1, EvEChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_ANG2, EvFChange),
  EV_CHILD_NOTIFY_ALL_CODES(TSB_TRUNK, EvGChange),
END_RESPONSE_TABLE;

Interface::Interface():TWindow(0,0,0)
{
  SetBkgndColor(TColor(R,G,B));
  genes[0]=0;      // # of offspring
  genes[1]=0;      // # number of iterations
  genes[2]=0;      // Branch length #1
  genes[3]=0;      // Branch length #2
  genes[4]=0;      // Branch combination
                   // Determines where on branch the "offshoot"
                   // will come from
  genes[5]=0;    // First angle
  genes[6]=0;     // Second angle
  genes[7]=0;     // Length of initial branch (trunk)
  Attr.W=632;
  Attr.H=520;
  Attr.X=100;
  Attr.Y=150;
  aVal = new TScrollBar(this, TSB_ITERATIONS, 500,0,96,24, true);
  bVal = new TScrollBar(this, TSB_BRLEN1,500,30,96,24,true);
  cVal = new TScrollBar(this, TSB_BRLEN2,500,60,96,24, true);
  dVal = new TScrollBar(this, TSB_COMBINE, 500,90,96,24, true);
  eVal = new TScrollBar(this, TSB_ANG1,500,120,96,24,true);
  fVal = new TScrollBar(this, TSB_ANG2,500,150,96,24, true);
  gVal = new TScrollBar(this, TSB_TRUNK,500,180,96,24, true);

  MainFontRec.lfHeight = -13;
  MainFontRec.lfWidth = -9;
  MainFontRec.lfEscapement = 0;
  MainFontRec.lfOrientation = 0;
  MainFontRec.lfWeight = FW_BOLD;
  MainFontRec.lfItalic = 0;
  MainFontRec.lfUnderline = 0;
  MainFontRec.lfStrikeOut = 0;
  MainFontRec.lfCharSet = ANSI_CHARSET;
  MainFontRec.lfOutPrecision = OUT_DEFAULT_PRECIS;
  MainFontRec.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  MainFontRec.lfQuality = PROOF_QUALITY;
  MainFontRec.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
  strcpy(MainFontRec.lfFaceName, "Times New Roman");

  myFont = new TFont(&MainFontRec);

  randomize();
}

void Interface::Paint(TDC& pdc, bool erase, TRect &rect)
{
  DisplayGraphic(true);
  DisplayGraphic(false);
  pdc.SelectObject(*myFont);
  pdc.SetBkColor(TColor(R,G,B));
  pdc.SetTextColor(TColor(23,55,95));
  char *buffer;
  buffer = new char[3];
  for (int i=0;i!=7;i++)
    {
      buffer = itoa(i+1,buffer,10);
      strcat(buffer,"\0");
      pdc.TextOut(480,(i*30),buffer);
    }
  pdc.RestoreFont();
  TWindow::Paint(pdc, erase, rect);
}

void Interface::DisplayGraphic(bool erase=false)
{
  TClientDC dc(*this);
  TPen *pen;
  if (erase)
    pen = new TPen(TColor(R,G,B),1,PS_SOLID);
  else
    pen = new TPen(TColor(0,0,0),1,PS_SOLID);
  dc.SelectObject(*pen);
  dc.MoveTo(200,200);
  dc.LineTo(200,200-genes[7]);
  Draw(dc, genes[1], 200,200-genes[7],19.8);
  dc.RestorePen();
}

void Interface::Draw(TClientDC &dc, int count, int x, int y, float rotation)
{
  if (count!=0)
    {
      count--;
      int length=0;
      if (IsEven(count))
        length = genes[2];
      else
        length = genes[3];

      // The main branch on the left

      dc.MoveTo(x,y);
      int newx = x - length * sin (rotation/M_2PI);
      int newy = y + length * cos (rotation/M_2PI);
      dc.LineTo(newx, newy);

      // The "offshoot" branch on the left

      newx = x - (((float)length/100)*genes[4]) * sin (rotation/M_2PI);
      newy = y + (((float)length/100)*genes[4]) * cos (rotation/M_2PI);
      dc.MoveTo(newx, newy);
      newx = x - length * sin ((19.5-genes[6])/M_2PI);
      newy = y + length * cos ((19.5-genes[6])/M_2PI);
      dc.LineTo(newx, newy);
      Draw(dc,count,newx,newy, rotation-genes[5]);

      // The main branch on the right

      dc.MoveTo(x,y);
      newx = x - length * sin (rotation/M_2PI);
      newy = y + length * cos (rotation/M_2PI);
      dc.LineTo(newx, newy);

      // The "offshoot" branch on the right

      newx = x - (((float)length/100)*genes[4]) * sin (rotation/M_2PI);
      newy = y + (((float)length/100)*genes[4]) * cos (rotation/M_2PI);
      dc.MoveTo(newx, newy);
      newx = x - length * sin ((19.5+genes[6])/M_2PI);
      newy = y + length * cos ((19.5+genes[6])/M_2PI);
      dc.LineTo(newx, newy);

      Draw(dc,count,newx,newy, rotation+genes[5]);
    }
}

void Interface::SetupWindow()
{
  aVal->SetRange(0,8);
  bVal->SetRange(0,5);
  cVal->SetRange(0,5);
  dVal->SetRange(0,100);
  eVal->SetRange(0,360);
  fVal->SetRange(0,360);
  gVal->SetRange(0,50);

  TWindow::SetupWindow();
}

void Interface::EvAChange(uint)
{
  DisplayGraphic(true);
  genes[1]=aVal->GetPosition();
  if (genes[1]>8)
    genes[1]=8;
  DisplayGraphic(false);
}

void Interface::EvBChange(uint)
{
  DisplayGraphic(true);
  genes[2]=bVal->GetPosition();
  DisplayGraphic(false);
}

void Interface::EvCChange(uint)
{
  DisplayGraphic(true);
  genes[3]=cVal->GetPosition();
  DisplayGraphic(false);
}

void Interface::EvDChange(uint)
{
  DisplayGraphic(true);
  genes[4]=dVal->GetPosition();
  DisplayGraphic(false);
}

void Interface::EvEChange(uint)
{
  DisplayGraphic(true);
  genes[5]=eVal->GetPosition();
  DisplayGraphic(false);
}

void Interface::EvFChange(uint)
{
  DisplayGraphic(true);
  genes[6]=fVal->GetPosition();
  DisplayGraphic(false);
}

void Interface::EvGChange(uint)
{
  DisplayGraphic(true);
  genes[7]=gVal->GetPosition();
  DisplayGraphic(false);
}


//=================================================

class InterfaceApp : public TApplication
{
  public:

    InterfaceApp() : TApplication() {}
    void InitMainWindow()
  {
    Interface *myInterface = new Interface ();
    TFrameWindow *myFrame =
      new TFrameWindow(0,"Graphic evolution program",myInterface,true);
    myFrame->Attr.Style &= ~WS_THICKFRAME;
    SetMainWindow(myFrame);
  }
};

//======================================
// MAIN LINE
//======================================

int OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return InterfaceApp().Run();
}


