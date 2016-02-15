/*======================================
Animator IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TWindow
======================================*/

#include "animator.h"

char *fileName;

// Response table definition

DEFINE_RESPONSE_TABLE1(Interface, TWindow)
  EV_COMMAND(TBU_EXIT, CloseWindow),
  EV_COMMAND(TBU_ANIM, Animate),
END_RESPONSE_TABLE;

//==================================
// CONSTRUCTOR
//==================================

Interface::Interface():TWindow(0,0,0)
{
  Attr.W=250;
  Attr.H=280;
  Attr.X=100;
  Attr.Y=150;

  animationArray = new ArrayClass();

  border = new TUIBorder(TRect(10,10,240,220), TUIBorder::Recessed);
  anim = new TButton(this,TBU_ANIM,"Animate",50,232,64,24);
  exit = new TButton(this,TBU_EXIT,"Exit",130,232,64,24);

  SetBkgndColor(TColor(defR,defG,defB));

  morph = new TBiomorph(true,defR, defG, defB, 60,50);

  ifstream    ifs(fileName, ios::in|ios::binary);
  ifs.seekg(0,ios::end);
  long lastposition=ifs.tellg();
  ifs.close();
  if (lastposition>9)
  {
    animationArray->loadContents(fileName);
    animationArray->resetPtr();
    int a,b,c,d,e,f,g,h,i,j,k;
    animationArray->getNext(a,b,c,d,e,f,g,h,i,j,k);
    morph->SetGenes(a,b,c,d,e,f,g,h,i,j,k);
  }
  else
    animationArray->addToArray(0,0,0,0,0,0,0,0,0,0,0);
}

//==================================
// DESTRUCTOR
//==================================

Interface::~Interface()
{
  delete animationArray;
  delete border;
  delete exit;
}

//==================================
// Paint
//
// The over-ridden Paint method for this class
//
// Receives: TDC object, an erase flag and a TRect object
//  Returns: Nothing
//==================================

void Interface::Paint(TDC &dc, bool erase, TRect &rect)
{
  border->Paint(dc);
  TClientDC cdc(*this);
  morph->Display(cdc,false);
  TWindow::Paint(dc, erase, rect);
};

//==================================
// CloseWindow
//
// The over-ridden CloseWindow method for this window
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::CloseWindow()
{
  TWindow::CloseWindow();
};

//==================================
// SetupWindow
//
// The over-ridden SetupWindow method for this window
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::SetupWindow()
{
  TClientDC dc(*this);
  morph->Display(dc,false);
  TWindow::SetupWindow();
}

//==================================
// Animate
//
// This method begins the anmation process.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::Animate()
{
  TClientDC dc(*this);
  clock_t wstart, wend;
  int a,b,c,d,e,f,g,h,i,j,k;
  int counter;
  animationArray->resetPtr();
  counter=animationArray->numElements() - 1;
  while (counter!=0)
    {
      morph->Display(dc,true);
      animationArray->getNext(a,b,c,d,e,f,g,h,i,j,k);
      animationArray->advancePtr();
      morph->SetGenes(a,b,c,d,e,f,g,h,i,j,k);
      morph->Display(dc,false);
      wend=0;
      wstart=clock();
      while (wend<(wstart+(.1*CLK_TCK)))
        wend=clock();
      counter--;
    }
};

//=================================================

class InterfaceApp : public TApplication
{
  public:

    InterfaceApp() : TApplication() {}
    void InitMainWindow()
  {
    Interface *myInterface = new Interface ();
    TFrameWindow *myFrame =
      new TFrameWindow(0,"Biomorph evolution animator",myInterface,true);
    myFrame->Attr.Style &= ~WS_THICKFRAME;
    SetMainWindow(myFrame);
  }
};

//======================================
// MAIN LINE
//======================================

int OwlMain(int argc, char* argv [])
{

  // This application REQUIRES that a command-line argument
  // be given.

  if (argc==2)
    {
      fileName=argv[1];
      return InterfaceApp().Run();
    }
}
