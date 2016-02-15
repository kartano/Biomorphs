/*======================================
TStatsDialog IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/uihelper.h>
#include "stats.h"
#include "part_b.h"

// Response table definition

DEFINE_RESPONSE_TABLE1(TStatsDialog, TDialog)
  EV_COMMAND(TBU_OK2, CloseWindow),
  EV_COMMAND(TBU_SHOW, ShowGraph),
END_RESPONSE_TABLE;

//===================================
// CONSTRUCTOR
//===================================

TStatsDialog::TStatsDialog(Interface *parent, TResId id):TDialog(parent, id,0)
{
  myParent=parent;
  ok = new TButton(this,TBU_OK2,"OK",130,365,80,30);
  show = new TButton(this,TBU_SHOW,"SHOW",250,365,80,30);
};

//===================================
// DESTRUCTOR
//===================================

TStatsDialog::~TStatsDialog()
{
  delete ok;
  delete show;
};

//==================================
// ShowGraph
//
// This routine draws the statistics graph.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

void TStatsDialog::ShowGraph()
{
  int a,b,c,d,e,f,g,h,i,j,k;

  // retrieve statistics from manager.

  myParent->GetStats(a,b,c,d,e,f,g,h,i,j,k);
  int stats[11];
  stats[0]=a;
  stats[1]=b;
  stats[2]=c;
  stats[3]=d;
  stats[4]=e;
  stats[5]=f;
  stats[6]=g;
  stats[7]=h;
  stats[8]=i;
  stats[9]=j;
  stats[10]=k;

  // Determine what the maximum value is.
  // This value is used to determine the values on the X axis.

  int max=0;
  for (int i=0;i!=11;i++)
    if (stats[i]>max)
      max=stats[i];

  TClientDC dc(*this);
  TPen pen(TColor(0,0,0));
  TPen filler(TColor(40,130,200));
  dc.SelectObject(pen);

  // Graw the axis and chart lines
  // Maximum X size for a bar on the chart: 300.
  // Maximum Y size for a bar on the chart: 20 + 5 for edge.

  dc.MoveTo(100,30);
  dc.LineTo(100,305);
  dc.LineTo(400,305);

  // Headings and axis values

  dc.SetBkMode(TRANSPARENT);
  dc.TextOut(10,10,"Gene number");
  dc.TextOut(350,340,"Number of changes");
  char *buffer;
  buffer = new char[10];
  for (int i=0;i!=11;i++)
    {
      buffer=itoa(i,buffer,10);
      dc.TextOut(70,30+i*25,buffer);
    }
  buffer=itoa(max,buffer,10);
  dc.TextOut(400,305,buffer);
  if (max>1)
    {
      buffer=itoa(max/2,buffer,10);
      dc.TextOut(250,305,buffer);
    }

  int length;

  // If the maximum was not zero ...

  if (max!=0)
    {

  // For each gene ...

      for (int i=0;i!=11;i++)
        {

          // If this gene has a value

          if (stats[i]!=0)
            {

              // Find the length of the line

              length=((stats[i]*300)/max);

              // Draw the bar outline

              dc.SelectObject(pen);
              dc.MoveTo(100,30+i*25);
              dc.LineTo(100+length,30+i*25);
              dc.MoveTo(100,50+i*25);
              dc.LineTo(100+length,50+i*25);
              dc.LineTo(100+length,30+i*25);
              dc.SelectObject(filler);
              dc.FloodFill(TPoint(99+length,31+i*25),TColor(0,0,0));
            }
        }
    }
};
