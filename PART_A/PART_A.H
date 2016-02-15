/*======================================

Interface INTERFACE

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
#include <owl/window.h>
#include <stdlib.h>
#include "part_a.rc"
#include "editexam.h"
#include "setupdia.h"
#include "resource.rh"
#include "evolve.h"

//#define DEBUG

#ifndef MAIN_PROJECT
#define MAIN_PROJECT

class Interface : public TWindow {
  public:
    Interface();
    void StartEvolution();
    void ShowReport();
    void OpenFile() {editOri->RestoreText();};
    void GetSettings();
    void AboutProgram();
    void Settings(int, int, int, bool, bool, bool, bool);
    void SetupWindow();

    // Statistics and settings, GETS and SETS

    int GetSeconds() {return seconds;}
    int GetMinChanges() {return minchanges;}
    int GetMaxChanges() {return maxchanges;}
    int GetGenerations() {return generations;}
    int GetDelayTime() {return delayTime;}
    int GetGenLimit() {return generationLimit;}
    bool GetNoDelState() {return noDelay;}
    bool GetDetailState() {return showAllDetails;}
    bool GetLimitState() {return limit;}
    bool GetStepState() {return stepState;}
    int GetStepNumber() {return stepNumber;}

  protected:

    TExampleEdit *editEvo, *editOri;
    EvolutionManager *evoManager;
    TOpenSaveDialog::TData FileData;
    void RetrieveFile();

  private:

    TButton *report;

    // Configuration information

    int delayTime, generationLimit, stepNumber;
    bool showAllDetails, noDelay, limit, stepState;

    // Statistics information

    int seconds, generations, maxchanges, minchanges;

    bool canShowReport;
    
    // Define the response table

  DECLARE_RESPONSE_TABLE(Interface);
};

#endif
