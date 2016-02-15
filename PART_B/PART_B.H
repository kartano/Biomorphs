/*======================================
Interface INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TWindow
======================================*/

#include <owl/uihelper.h>
#include <owl/dc.h>
#include <owl/dialog.h>
#include <owl/static.h>
#include <stdlib.h>
#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/decframe.h>
#include <owl/inputdia.h>
#include <owl/button.h>
#include <owl/radiobut.h>
#include <owl/groupbox.h>
#include <owl/opensave.h>
#include "manager.h"
#include "array.h"

// The #ifndef lines here are used to prevent
// recusrive inclusion from within the header files

#ifndef EDIT
#define EDIT
#include "edit.h"
#endif
#ifndef GENE_VALUES
#define GENE_VALUES
#include "genes.h"
#endif
#ifndef STATS
#define STATS
#include "stats.h"
#endif
#ifndef OFFSPRING
#define OFFSPRING
#include "offsprin.h"
#endif

#include "resourc2.rh"
#include "part_b.rc"

#ifndef APPLICATION_INTERFACE
#define APPLICATION_INTERFACE

// Define the background color elements

const int defR = 190;
const int defG = 190;
const int defB = 190;

class Interface : public TWindow
{

  public:

    Interface();
    ~Interface();
    void SetupWindow();
    void About();
    void Paint(TDC&, bool, TRect&);
    void EvLButtonDown(uint, TPoint&);
    void EvRButtonDown(uint, TPoint&);
    void AlterGenes(int, int, int, int, int, int, int, int, int, int, int);
    void OpenParent();
    void SaveParent();
    void CloseWindow();
    void Colors();
    void CeEnableRecord(TCommandEnabler&);
    void CeEnableStop(TCommandEnabler&);
    void CeUseColors(TCommandEnabler&);
    void CeMaxOffspring(TCommandEnabler&);
    void StartRecording();
    void StopRecording();
    void GetStats(int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,int&);
    int GetBoxCount(int index) {return boxCount[index];};
    void ToggleMaxOffspring() {maxOffspring=!maxOffspring;};

  protected:

    TOpenSaveDialog::TData FileData;

    void New();
    void DrawMorphs(int);
    void EditBiomorph();
    void Statistics();
    void Offspring();

    // Interface elements

    TUIBorder *box1, *box2, *box3, *box4, *box5, *box6, *box7, *box8, *box9, *box10,
            *box11, *box12, *parent;

    TButton *edit;

    // coordinates of each of the boxes which hold 'morphs.

    int box, oldbox;
    int boxes[12][4];
    int boxCount[12];

    // Evolution manager

    TManager *manager;

    // Array class to save "animations"

    ArrayClass *animationArray;

    bool recording, stop, changed, maxOffspring, useColors;

    int numFrames;

    #ifdef DEBUG
    int clickCount;
    #endif

  // Declare the response table for the interface

  DECLARE_RESPONSE_TABLE(Interface);
};

#endif

