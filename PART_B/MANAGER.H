/*======================================
TManager INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/

#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/dc.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/opensave.h>
#include <owl/static.h>
#include <stdlib.h>
#include "resourc2.rh";
#ifndef ONE
#define ONE
#include "manager.h"
#endif
#ifndef TWO
#define TWO
#include "biomorph.h"
#endif

#ifndef BIOMORPH_MANAGER
#define BIOMORPH_MANAGER

class TManager
{
  public:

    TManager(bool, int, int, int);
    ~TManager();
    void SetRegion(int, int, int, int, int);
    void SetParent(TClientDC&, int, bool);
    void SetParentGenes(TClientDC&, int, int, int, int, int, int, int, int, int, int, int);
    void GetParent(int &, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
    void GetMorph(int, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
    void SetParentGene(int, int);
    void Draw(TClientDC&, bool);
    bool IsActive(int index){return active[index];};
    void SetColors(bool);
    void GetStats(int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,int&);
    void ResetBiomorphs();
    
  protected:

    // "Active" flags. If a flag is active, then its
    // corresponding box has a biomorph in it.

    bool active[12];

    // The biomorphs

    TBiomorph *morph1, *morph2, *morph3, *morph4,
              *morph5, *parent,          *morph6,
              *morph7,                   *morph8,
              *morph9, *morph10, *morph11, *morph12;
    int boxes[12][4];

    // Array to keep count of which genes mutate

    int geneChanges[11];
};

#endif