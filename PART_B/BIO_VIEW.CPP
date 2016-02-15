//===============================
// interface IMPLEMENTATION
//
// By Simon Mitchell (96878291)
//
// Base classes: TWindow
//===============================

#include "bio_view.h"

//==================================
// CONSTRUCTOR
//==================================

char *theName;

Interface::Interface(char *name):TWindow(0,0,0)
{
  Attr.W=200;
  Attr.H=200;
  Attr.X=100;
  Attr.Y=150;
  SetBkgndColor(TColor(r,g,b));
  myMorph=new TBiomorph(true,r,g,b,40,40);
  int a,b,c,d,e,f,g,h,i,j,k;
  ifstream ifs(theName);
  a=(unsigned char)ifs.get();
  b=(unsigned char)ifs.get();
  c=(unsigned char)ifs.get();
  d=(unsigned char)ifs.get();
  e=(unsigned char)ifs.get();
  f=(unsigned char)ifs.get();
  g=(unsigned char)ifs.get();
  h=(unsigned char)ifs.get();
  i=(unsigned char)ifs.get();
  j=(unsigned char)ifs.get();
  k=(unsigned char)ifs.get();
  ifs.close();
  myMorph->SetGenes(a,b,c,d,e,f,g,h,i,j,k);
}

//==================================
// DESTRUCTOR
//==================================

Interface::~Interface()
{
  delete myMorph;
}

void Interface::Paint(TDC &dc, bool erase, TRect &rect)
{
  TClientDC newDc (*this);
  myMorph->Display(newDc,false);
  TWindow::Paint(dc, erase, rect);
};

//=================================================

class InterfaceApp : public TApplication
{
  public:

    InterfaceApp() : TApplication() {}
    void InitMainWindow()
  {
    Interface *myInterface = new Interface (theName);
    TFrameWindow *myFrame =
      new TFrameWindow(0,"Biomorph viewer",myInterface,true);
    myFrame->Attr.Style &= ~WS_THICKFRAME;
    SetMainWindow(myFrame);
  }
};

//======================================
// MAIN LINE
//======================================

int OwlMain(int argc, char* argv [])
{
  if (argc==2)
    {
      theName=argv[1];
      return InterfaceApp().Run();
    }
}

