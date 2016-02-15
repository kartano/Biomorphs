/*======================================

TExampleEdit IMPLEMENTATION

By Simon Mitchell (96878291)

  Standard TEdit box with new methods for extra
functionality.

  Based on Edit Box example supplied with
Borland C++ V5.02 CD:

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
#include <stdlib.h>

#include "edit.rh"
#include "editexam.h"

// Size of the text buffer: Defaults to 500K, may be clipped
// if exceeds that length by system.

const unsigned TExampleEdit::EditTextLen   = 500000;

//-------------------------------------
// SetupWindow
//
// Calls TEdit SetupWindow and defines file data flags
// used for open/save
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::SetupWindow()
{
  TEdit::SetupWindow();
  FileData.Flags = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
  FileData.SetFilter("Text files (*.TXT)|*.TXT|AllFiles (*.*)|*.*|");
}

//-------------------------------------
// CmEditCut
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditCut()
{
  LastCBOpStr = "Cut";
  NotifyParent(CN_UPDATE);
  TEdit::CmEditCut();
  NotifyParent(CN_UPDATE);
  TEdit::CmEditCut();
}

//-------------------------------------
// CmEditCopy
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditCopy()
{
  LastCBOpStr = "Copy";
  NotifyParent(CN_UPDATE);
  TEdit::CmEditCopy();
}

//-------------------------------------
// CmEditPaste
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditPaste()
{
  LastCBOpStr = "Paste";
  NotifyParent(CN_UPDATE);
  TEdit::CmEditPaste();
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// CmEditDelete
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditDelete()
{
  LastCBOpStr = "Delete";
  NotifyParent(CN_UPDATE);
  TEdit::CmEditDelete();
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// CmEditClear
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditClear()
{
  TEdit::CmEditClear();
  LastCBOpStr = "Clear";
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// CmEditUndo
//
// Records last action, calls TEdit method
// and notifies parent of change.
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::CmEditUndo()
{
  TEdit::CmEditUndo();
  LastCBOpStr = "Undo";
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// EvKeyDown
//
// Responds to a key press in the text box
//
// Receives: code for pressed key, repeat count, display flags
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::EvKeyDown(uint key, uint repeatCount, uint flags)
{
  TEdit::EvKeyDown(key, repeatCount, flags);
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// EvLButtonDown
//
// Responds to a left mouse button click
//
// Receives: key code, point
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::EvLButtonDown(uint modKeys, TPoint& point)
{
  TEdit::EvLButtonDown(modKeys, point);
  NotifyParent(CN_UPDATE);
}

//-------------------------------------
// NotifyParent
//
// Sends message to parent
//
// Receives: Message code
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::NotifyParent(int notification)
{
  Parent->SendNotification(Attr.Id, notification, HWindow);
}

//-------------------------------------
// SaveText
//
// Saves contents of text box to text file
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::SaveText()
{
  if (TFileSaveDialog(GetApplication()->MainWindow, FileData).Execute() == IDOK) {
    ofstream    ofs(FileData.FileName, ios::out|ios::binary);
    unsigned    maxLen = EditTextLen;
    char far*   buffer = LockBuffer();
    unsigned    size = min(maxLen, strlen(buffer));

    for (unsigned i = 0; i < size && buffer[i]; i++)
      ofs.put(buffer[i]);
    UnlockBuffer(buffer);
  }
}

//-------------------------------------
// RestoreText
//
// Restores or loads text from a file into edit box
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::RestoreText()
{
  if (TFileOpenDialog(GetApplication()->MainWindow, FileData).Execute() == IDOK) {
    Clear();

    ifstream    ifs(FileData.FileName);
    char far*   buffer = LockBuffer(EditTextLen + 1);

    unsigned i;
    for (i = 0; i < EditTextLen && !ifs.eof(); i++) {
      buffer[i] = (char)ifs.get();
      if (buffer[i] == '\n' && ifs.peek() != '\r') {
        buffer[i] = '\r';
        buffer[++i] = '\n';
      }
    }
    if (i)
      buffer[i-1] = 0;
    UnlockBuffer(buffer, TRUE);
    NotifyParent(CN_UPDATE);
  }
}

//-------------------------------------
// returnBuffer
//
// Locks text edit buffer
//
// Receives: Nothing
//  Returns: Pointer to start of text edit buffer
//-------------------------------------

char far * TExampleEdit::returnBuffer()
{
  myBuffer = LockBuffer(EditTextLen + 1);
  return myBuffer;
}

//-------------------------------------
// resetBuffer
//
// Unlocks the text edit buffer
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::resetBuffer()
{
  UnlockBuffer(myBuffer, TRUE);
}

//-------------------------------------
// getLength
//
// Returns maxmimum length for this text edit buffer
//
// Receives: Nothing
//  Returns: Maxmimum length of edit buffer
//-------------------------------------

unsigned TExampleEdit::getLength()
{
  return EditTextLen + 1;
}

//-------------------------------------
// UpdateDisplay
//
// This method passes a "paint" message on to the parent (or "super") class
//
// Receives: Nothing
//  Returns: Nothing
//-------------------------------------

void TExampleEdit::UpdateDisplay()
{
  NotifyParent(WM_PAINT);
}
