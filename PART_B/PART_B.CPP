/*======================================
Interface IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TWindow
======================================*/

#include "part_b.h"

// Response table definition

DEFINE_RESPONSE_TABLE1(Interface, TWindow)
  EV_WM_LBUTTONDOWN,
  EV_WM_RBUTTONDOWN,
  EV_COMMAND(CM_EXIT, CloseWindow),
  EV_COMMAND(CM_ABOUT, About),
  EV_COMMAND(CM_OPENPARENT, OpenParent),
  EV_COMMAND(CM_SAVEPARENT, SaveParent),
  EV_COMMAND(TBU_EDIT, EditBiomorph),
  EV_COMMAND(CM_STARTRECORD, StartRecording),
  EV_COMMAND(CM_STOPRECORD, StopRecording),
  EV_COMMAND(CM_COLORS, Colors),
  EV_COMMAND(CM_GENEMUTATIONS, Statistics),
  EV_COMMAND(CM_OFFSPRING, Offspring),
  EV_COMMAND(CM_MAXOFFSPRING, ToggleMaxOffspring),
  EV_COMMAND(CM_NEW, New),
  EV_COMMAND_ENABLE(CM_STOPRECORD, CeEnableStop),
  EV_COMMAND_ENABLE(CM_STARTRECORD, CeEnableRecord),
  EV_COMMAND_ENABLE(CM_COLORS, CeUseColors),
  EV_COMMAND_ENABLE(CM_MAXOFFSPRING, CeMaxOffspring),
END_RESPONSE_TABLE;

//==================================
// CONSTRUCTOR
//==================================

Interface::Interface():TWindow(0,0,0)
{
  #ifdef DEBUG
  clickCount=0;
  ofstream ofs(DEBUG_FILE,ios::out);
  ofs.close();
  #endif

  numFrames=0;
  recording=false;
  stop=true;
  maxOffspring=false;
  useColors=true;

  Attr.W=532;
  Attr.H=520;
  Attr.X=100;
  Attr.Y=150;

  int i=0;
  for (i=0;i!=4;i++)
    {

      // Coordinates of top row of boxes

      boxes[i][0]=10+(130*i);        // x1
      boxes[i][1]=5;                 // y1
      boxes[i][2]=130+(130*i);       // x2
      boxes[i][3]=125;               // y2

      // Coordinates of bottom row of boxes

      boxes[i+8][0]=10+(130*i);      // x1
      boxes[i+8][1]=395;             // y1
      boxes[i+8][2]=130+(130*i);     // x2
      boxes[i+8][3]=515;             // y2
    }

  boxes[4][0]=boxes[6][0]=10;
  boxes[4][1]=boxes[5][1]=135;
  boxes[4][2]=boxes[6][2]=130;
  boxes[4][3]=boxes[5][3]=255;

  boxes[5][0]=boxes[7][0]=400;
  boxes[5][2]=boxes[7][2]=520;

  boxes[6][1]=boxes[7][1]=265;
  boxes[6][3]=boxes[7][3]=385;

  manager = new TManager(useColors, defR, defG, defB);
  animationArray = new ArrayClass();

  #ifdef DEBUG
  ofstream ofs2(DEBUG_FILE,ios::app);
  ofs2 << "*** INSIDE INTERFACE ***\n";
  ofs2 << "Method called: Constructor\n";
  ofs2 << "manager of type TManager created.\n";
  ofs2 << "animationArray of type ArrayClass created.\n\n";
  ofs2.close();
  #endif

  for (i=0;i!=12;i++)
    {
      manager->SetRegion(i,boxes[i][0], boxes[i][1],boxes[i][2],boxes[i][3]);
      boxCount[i]=0;
    }

  i=0;

  box1 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box2 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box3 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box4 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;

  box5 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box6 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;

  box7 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box8 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;

  box9 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box10 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box11 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);
  i++;
  box12 = new TUIBorder(TRect(boxes[i][0],boxes[i][1],boxes[i][2],boxes[i][3]), TUIBorder::Recessed);

  parent = new TUIBorder(TRect(140,135,390,355),TUIBorder::Recessed);

  edit = new TButton(this,TBU_EDIT,"Edit",230,362,64,24);

  SetBkgndColor(TColor(defR,defG,defB));

  FileData.Flags = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
  FileData.SetFilter("Biomorphs (*.BMF)|*.BMF|AllFiles (*.*)|*.*|");
}

//==================================
// DESTRUCTOR
//==================================

Interface::~Interface()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: Destructor\n";
  #endif
  delete manager;
  delete edit;
  delete animationArray;
  #ifdef DEBUG
  ofs << "manager of type TManager DELETED:     " << sizeof(TManager) << " bytes\n";
  ofs << "edit of type TButton DELETED:         " << sizeof(TButton) << " bytes\n";
  ofs << "animationArray of type Array DELETED: " << sizeof(ArrayClass) << " bytes\n\n";
  ofs.close();
  #endif
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
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: Paint\n\n";
  ofs.close();
  #endif
  TClientDC DragDC(*this);
  manager->Draw(DragDC, false);

  box1->Paint(dc);
  box2->Paint(dc);
  box3->Paint(dc);
  box4->Paint(dc);
  box5->Paint(dc);
  box6->Paint(dc);
  box7->Paint(dc);
  box8->Paint(dc);
  box9->Paint(dc);
  box10->Paint(dc);
  box11->Paint(dc);
  box12->Paint(dc);
  parent->Paint(dc);

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
// EvLButtonDown
//
// This method handles a left mouse button click
//
// Receives: Uint identifier and a TPoint co-ordinate
//  Returns: Nothing
//==================================

void Interface::EvLButtonDown(uint, TPoint &point)
{
  int x=point.x;
  int y=point.y;
  int i;
  int mybox=-1;
  for (i=0;i!=12;i++)
    if (((x>=boxes[i][0])&&(x<=boxes[i][2]))&&((y>=boxes[i][1])&&(y<=boxes[i][3])))
      mybox=i;

  if (mybox!=-1)
    {

      #ifdef DEBUG
      clickCount++;
      ofstream ofs(DEBUG_FILE,ios::app);
      ofs << "*** INSIDE INTERFACE ***\n";
      ofs << "Method called: EvLButtonDown\n";
      ofs << "Click count is now: " << clickCount << "\n";
      ofs << "Morph chosen was:   " << mybox << "\n\n";
      ofs.close();
      #endif

      DrawMorphs(mybox);
    }

  // If we're recording, add the gene values to the array

  if (recording)
    {
      numFrames++;
      int a,b,c,d,e,f,g,h,i,j,k;
      manager->GetParent(a,b,c,d,e,f,g,h,i,j,k);
      animationArray->addToArray(a,b,c,d,e,f,g,h,i,j,k);
    }

  // Repaint all the boxes when the biormorphs are drawn

  TClientDC dc(*this);
  box1->Paint(dc);
  box2->Paint(dc);
  box3->Paint(dc);
  box4->Paint(dc);
  box5->Paint(dc);
  box6->Paint(dc);
  box7->Paint(dc);
  box8->Paint(dc);
  box9->Paint(dc);
  box10->Paint(dc);
  box11->Paint(dc);
  box12->Paint(dc);
  parent->Paint(dc);
}

//==================================
// New
//
// This method resets the manager and effectively starts
// the biomorph evolution process from scratch.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::New()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: New\n\n";
  ofs.close();
  #endif

  // Display an informative message if the user was recording.

  if (recording)
    MessageBox("All biomorphs stored for animation have been lost","Recording",MB_OK|MB_ICONEXCLAMATION);
  numFrames=0;
  recording=false;
  stop=true;
  maxOffspring=false;
  useColors=true;
  animationArray->emptyArray();
  TClientDC DragDC(*this);

  // Reset all the biomorphs and related statistics

  manager->Draw(DragDC, true);
  manager->ResetBiomorphs();
  manager->Draw(DragDC, false);
  for (int i=0;i!=12;i++)
    boxCount[i]=0;
};

//==================================
// EvRButtonDown
//
// This method handles a right mouse button click
//
// Receives: Uint identifier and a TPoint co-ordinate
//  Returns: Nothing
//==================================

void Interface::EvRButtonDown(uint, TPoint &point)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: EvRButtonDown\n";
  ofs << "Co-ords:   X = " << point.x << "\n";
  ofs << "           Y = " << point.y << "\n";
  #endif

  int x=point.x;
  int y=point.y;
  int mybox=-1;
  int index;
  for (index=0;index!=12;index++)
    if (((x>=boxes[index][0])&&(x<=boxes[index][2]))&&((y>=boxes[index][1])&&(y<=boxes[index][3])))
      mybox=index;
  if ((manager->IsActive(mybox))&&(mybox!=-1))
    {
      #ifdef DEBUG
      ofs << "Box clicked: " << mybox << "\n";
      #endif

      int a,b,c,d,e,f,g,h,i,j,k;
      manager->GetMorph(mybox,a,b,c,d,e,f,g,h,i,j,k);

      #ifdef DEBUG
      ofs << "Gene values:  " << a << " " << b << " " << c << " "
          << d << " " << e << " " << f << " " << g << " "
          << h << " " << i << " " << j << " " << k << "\n\n";
      ofs.close();
      #endif

      TGenesDialog geneValues(this, IDD_GENEVALUES,a,b,c,d,e,f,g,h,i,j,k);
      geneValues.Execute();
    }
}

//==================================
// DrawMorphs
//
// This routine tells the biomorph manager which biomorph it
// needs to draw.
//
// Receives: Index for the biomorph to be drawn
//  Returns: Nothing
//==================================

void Interface::DrawMorphs(int box)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: DrawMorphs\n";
  ofs << "Box value: " << box << "\n";
  ofs << "Box is active? ";
  (manager->IsActive(box)) ? ofs << "YES\n\n" : ofs << "NO\n\n";
  ofs.close();
  #endif

  if (manager->IsActive(box))
    {
      boxCount[box]++;
      TClientDC DragDC(*this);
      manager->Draw(DragDC, true);
      if (box!=-1)
        manager->SetParent(DragDC, box, maxOffspring);
      manager->Draw(DragDC, false);
    }
}

//==================================
// EditBiomorph
//
// This routine creates the biomorph edit box and allows
// the user to then alter all the genes within the current
// parent.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::EditBiomorph()
{
  int a, b, c, d, e, f, g, h, i, j, k;
  manager->GetParent(a,b,c,d,e,f,g,h,i,j,k);

  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: EditBiomorph\n";
  ofs << "Gene values:  " << a << " " << b << " " << c << " "
      << d << " " << e << " " << f << " " << g << " "
      << h << " " << i << " " << j << " " << k << "\n\n";
  ofs.close();
  #endif

  TEditDialog editDialog(this, IDD_DIALOG2, a,b,c,d,e,f,g,h,i,j,k,useColors);
  changed = false;
  editDialog.Execute();
  if (changed)
    DrawMorphs(0);
}

//==================================
// AlterGenes
//
// This routine is called be the EDIT BIORMORPH dialog box.
// It accepts the new values for the parent and passes these
// on to the evolution manager.
//
// Receives: New gene values
//  Returns: Nothing
//==================================

void Interface::AlterGenes(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
  TClientDC newDc(*this);
  if (maxOffspring)
    a=12;
  manager->SetParentGenes(newDc,a,b,c,d,e,f,g,h,i,j,k);
  changed=true;
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: AlterGenes\n";
  ofs << "Gene values:  " << a << " " << b << " " << c << " "
      << d << " " << e << " " << f << " " << g << " "
      << h << " " << i << " " << j << " " << k << "\n\n";
  ofs.close();
  #endif

}

//==================================
// SetupWindow
//
// The standard over-ridden SetupWindow method for this class
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::SetupWindow()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: SetupWindow\n\n";
  ofs.close();
  #endif
  TClientDC dc(*this);
  manager->Draw(dc,false);
  TWindow::SetupWindow();
}

//==================================
// About
//
// This method will display the About dialog box
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::About()
{
  TDialog aboutThis(this, IDD_DIALOG1);
  aboutThis.Execute();
};

//==================================
// OpenParent
//
// This method allows the user to open a new parent biomorph
// from disk.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::OpenParent()
{
  if (TFileOpenDialog(GetApplication()->MainWindow, FileData).Execute() == IDOK)
    {
      int a,b,c,d,e,f,g,h,i,j,k;
      ifstream    ifs(FileData.FileName);
      try
        {
          a=(byte)ifs.get();
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
          #ifdef DEBUG
          ofstream ofs(DEBUG_FILE,ios::app);
          ofs << "*** INSIDE INTERFACE ***\n";
          ofs << "Method called: OpenParent\n";
          ofs << "Gene values: " << a << " " << b << " " << c << " "
              << d << " " << e << " " << f << " " << g << " "
              << h << " " << i << " " << j << " " << k << "\n\n";
          ofs.close();
          #endif
        }

      // This catch statement will catch ANY exception,
      // hence the ( ... ) - legal C++ syntax!

      catch ( ... )
        {
          MessageBox("AN I/O ERROR HAS OCCURRED!","ERROR",MB_OK|MB_ICONSTOP);
        }
      TClientDC newDc(*this);


      // Alter the genes for the parent and force the
      // biomorph manager to generate a new number of
      // offspring.

      AlterGenes(a,b,c,d,e,f,g,h,i,j,k);
      DrawMorphs(0);
      ifs.close();
    }
};

//==================================
// Colors
//
// Toggle the "use colors" flag and send a message to
// the evolution manager that this flag has changed.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::Colors()
{
  useColors=!useColors;
  manager->SetColors(useColors);
};

//==================================
// SaveParent
//
// This method allows the user to save a new parent biomorph
// to disk.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::SaveParent()
{
  if (TFileSaveDialog(GetApplication()->MainWindow, FileData).Execute() == IDOK)
    {
      ofstream    ofs(FileData.FileName, ios::out|ios::binary);
      int a,b,c,d,e,f,g,h,i,j,k;
      manager->GetParent(a,b,c,d,e,f,g,h,i,j,k);
      ofs.put((unsigned char)a);
      ofs.put((unsigned char)b);
      ofs.put((unsigned char)c);
      ofs.put((unsigned char)d);
      ofs.put((unsigned char)e);
      ofs.put((unsigned char)f);
      ofs.put((unsigned char)g);
      ofs.put((unsigned char)h);
      ofs.put((unsigned char)i);
      ofs.put((unsigned char)j);
      ofs.put((unsigned char)k);

      #ifdef DEBUG
      ofstream debugfs(DEBUG_FILE,ios::app);
      debugfs << "*** INSIDE INTERFACE ***\n";
      debugfs << "Method called: SaveParent\n";
      debugfs << "Gene values:  " << a << " " << b << " " << c << " "
          << d << " " << e << " " << f << " " << g << " "
          << h << " " << i << " " << j << " " << k << "\n\n";
      debugfs.close();
      #endif

      ofs.close();
    }
};

//==================================
// StartRecording
//
// This method is called when the "start recording"
// item from the Animations menu is selected.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::StartRecording()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE INTERFACE ***\n";
  ofs << "Method called: StartRecording\n\n";
  ofs.close();
  #endif

  numFrames=0;
  recording=true;
  stop=false;
};

//==================================
// StopRecording
//
// This method is called when the "stop recording"
// item from the Animations menu is selected.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::StopRecording()
{
  TOpenSaveDialog::TData SaveData;

  SaveData.Flags = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
  SaveData.SetFilter("Animation (*.BAN)|*.BAN|AllFiles (*.*)|*.*|");

  // Make sure there is at least one frame to save

  if (numFrames>0)
    {
      if (TFileSaveDialog(GetApplication()->MainWindow, SaveData).Execute() == IDOK)
        {
          #ifdef DEBUG
          ofstream ofs(DEBUG_FILE,ios::app);
          ofs << "*** INSIDE INTERFACE ***\n";
          ofs << "Method called: StopRecording\n\n";
          ofs.close();
          #endif
          animationArray->saveContents(SaveData.FileName);
          animationArray->emptyArray();
          recording=false;
          stop=true;
        }
      }
  else
    {
      MessageBox("No frames to save!","Stop recording",MB_OK|MB_ICONEXCLAMATION);
      recording=false;
      stop=true;
    }
};

//==================================
// CeEnableRecord
//
// This method sets the "enable" flag on the "start recording"
// menu item
//
// Receives: Address of a command enabler
//  Returns: Nothing
//==================================

void Interface::CeEnableRecord(TCommandEnabler &ce)
{
  ce.Enable(!recording);
}

//==================================
// CeEnableStop
//
// This method sets the "enable" flag on the "stop recording"
// menu item
//
// Receives: Address of a command enabler
//  Returns: Nothing
//==================================

void Interface::CeEnableStop(TCommandEnabler &ce)
{
  ce.Enable(!stop);
}

//==================================
// CeUseColors
//
// Sets the check mark for the "use colors" menu option.
//
// Receives: Address of a command enabler
//  Returns: Nothing
//==================================

void Interface::CeUseColors(TCommandEnabler &ce)
{
  ce.SetCheck(useColors);
}

//==================================
// CeMaxOffspring
//
// Sets the check mark for the "Maximum offspring" menu option.
//
// Receives: Address of a command enabler
//  Returns: Nothing
//==================================

void Interface::CeMaxOffspring(TCommandEnabler &ce)
{
  ce.SetCheck(maxOffspring);
}

//==================================
// Statistics
//
// Creates the statistics dialog and executes it.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::Statistics()
{
  TStatsDialog statsDialog(this, IDD_STATISTICS);
  statsDialog.Execute();
};

//==================================
// Offspring
//
// Creates the offspring count dialog and executes it.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void Interface::Offspring()
{
  TOffspringDialog offspringDialog(this, IDD_OFFSPRING);
  offspringDialog.Execute();
};

//==================================
// GetStats
//
// Retrieves all the statistics values from the
// evolution manager. Typically called by the
// statistics dialog.
//
// Receives: Addresses of integers to store stats into.
//  Returns: Nothing
//==================================

void Interface::GetStats(int&a,int&b,int&c,int&d,int&e,int&f,int&g,int&h,int&i,int&j,int&k)
{
   manager->GetStats(a,b,c,d,e,f,g,h,i,j,k);
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
      new TFrameWindow(0,"Graphic evolution program",myInterface,true);
    myFrame->Attr.Style &= ~WS_THICKFRAME;
    SetMainWindow(myFrame);
    GetMainWindow()->AssignMenu("COMMANDS");
  }
};

//======================================
// MAIN LINE
//======================================

int OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return InterfaceApp().Run();
}

