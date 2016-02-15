/*======================================

TExampleEdit INTERFACE

  This class is based on the Edit Box example as
supplied on the Borland C++ V5.02 CD:

bc5/examples/owl

BASE CLASSES: TEdit
======================================*/

#include <owl/pch.h>
#include <owl/applicat.h>
#include <owl/framewin.h>
#include <owl/static.h>
#include <owl/edit.h>
#include <owl/inputdia.h>
#include <owl/opensave.h>
#include <owl/validate.h>
#include <fstream.h>
#include <cstring.h>

#include "edit.rh"

#ifndef EXAMPLE_EDIT_BOX
#define EXAMPLE_EDIT_BOX

const int CN_UPDATE             = 300;

 class TExampleEdit : public TEdit {
  public:
    TExampleEdit(TWindow*        parent,
                 int             id,
                 const char far* text,
                 int x, int y, int w, int h,
                 uint            textLen = EditTextLen + 1,
                 bool            multiline = true,
                 TModule*        module = 0 )
    :
      TEdit(parent, id, text, x, y, w, h, textLen, multiline, module)
    {
      LastCBOpStr = " ";
    }

    void UpdateDisplay();
    void SetupWindow();
    void    CmEditCut();                   // CM_EDITCUT
    void    CmEditCopy();                  // CM_EDITCOPY
    void    CmEditPaste();                 // CM_EDITPASTE
    void    CmEditDelete();                // CM_EDITDELETE
    void    CmEditClear();                 // CM_EDITCLEAR
    void    CmEditUndo();                  // CM_EDITUNDO
    void    EvKeyDown(uint key, uint repeatCount, uint flags);
    void    EvLButtonDown(uint modKeys, TPoint& point);

    void NotifyParent(int notification);
    void SaveText();
    void RestoreText();
    const string& GetLastCBOpStr() const {return LastCBOpStr;}

    string                  LastCBOpStr;   // string value of last CB operation.
    static const unsigned   EditTextLen;   // length of edit control text.
    char far * returnBuffer();
    void resetBuffer();
    unsigned getLength();

  private:

    // save/restore info.

    TOpenSaveDialog::TData  FileData;

    // Text buffer

    char far *myBuffer;

    // Response table declaration

  DECLARE_RESPONSE_TABLE(TExampleEdit);
};

// Response table entries

DEFINE_RESPONSE_TABLE1(TExampleEdit, TEdit)
  EV_COMMAND(CM_EDITCUT,     CmEditCut),
  EV_COMMAND(CM_EDITCOPY,    CmEditCopy),
  EV_COMMAND(CM_EDITPASTE,   CmEditPaste),
  EV_COMMAND(CM_EDITDELETE,  CmEditDelete),
  EV_COMMAND(CM_EDITCLEAR,   CmEditClear),
  EV_COMMAND(CM_EDITUNDO,    CmEditUndo),
  EV_WM_KEYDOWN,
  EV_WM_LBUTTONDOWN,
END_RESPONSE_TABLE;

#endif
