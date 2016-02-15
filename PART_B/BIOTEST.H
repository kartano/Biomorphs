#include <owl/uihelper.h>
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/static.h>
#include <owl/scrollba.h>
#include <stdlib.h>

class Interface : public TWindow
{
  public:

    Interface();
    void Paint(TDC&, bool, TRect&);
    void CloseWindow();
    void SetupWindow();

  protected:

    void DisplayGraphic(bool);
    void Draw(TClientDC&,int, int, int, float);
    void EvAChange(uint);
    void EvBChange(uint);
    void EvCChange(uint);
    void EvDChange(uint);
    void EvEChange(uint);
    void EvFChange(uint);
    void EvGChange(uint);

    bool IsEven(int value) {return (value==((value/2)*2));};

    int width, height, numpoints;
    int genes[8];
    TScrollBar *aVal, *bVal, *cVal, *dVal, *eVal, *fVal, *gVal;

    LOGFONT MainFontRec;

    TFont *myFont;
    
  DECLARE_RESPONSE_TABLE(Interface);
};