/*======================================
TBiomorph INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/

#include "resourc2.rh"

#ifndef BIOMORPH
#define BIOMORPH

class TBiomorph
{
  public:

    TBiomorph(bool, int, int, int, int, int);
    ~TBiomorph();
    void Display(TClientDC &, bool erase);
    void SetGenes(int, int, int, int, int, int, int, int, int, int, int);
    void GetGenes(int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,int&);
    void SetX(int newx){xoff=newx;};
    void SetY(int newy){yoff=newy;};
    void SetXY(int, int);
    int Mutate();
    int GetGene(int index){return genes[index];};
    void SetGene(int, int);
    void UseColors(bool flag){useColors=flag;};

  protected:

    void Draw(TClientDC&, int, int, int, float);
    bool IsEven(int value) {return (value==((value/2)*2));};

    // Application background color elements, x and y offsets
    // for drawing bimorph

    int red, green, blue, xoff, yoff;
    float drawAngle;

    // The gene values

    int genes[12];

    // Flag to determine if we should mutate the colors or not.
    // If this flag is set to FALSE then all biomorphs will automatically
    // stay BLACK.

    bool useColors;
};

#endif
