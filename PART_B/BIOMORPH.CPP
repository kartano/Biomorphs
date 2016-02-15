/*======================================
TBiomorph IMPLEMENTATION

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
#include <math.h>
#include "biomorph.h"
#include "resourc2.rh"

//==================================
// CONSTRUCTOR
//==================================

TBiomorph::TBiomorph(bool flag,int R, int G, int B, int xx=0, int yy=0)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: Constructor\n\n";
  ofs.close();
  #endif
  red=R;
  green=G;
  blue=B;
  xoff=xx;
  yoff=yy;
  SetGenes(0,0,0,0,0,0,0,0,0,0,0);
  UseColors(flag);
}

//==================================
// DESTRUCTOR
//==================================

TBiomorph::~TBiomorph()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: Destructor\n\n";
  ofs.close();
  #endif
}

//==================================
// SetGenes
//
// This method accepts the new gene values and stores them.
//
// Receives: A list of integer values
//  Returns: Nothing
//==================================

void TBiomorph::SetGenes
  (int a,
   int b,
   int c,
   int d,
   int e,
   int f,
   int g,
   int h,
   int i,
   int j,
   int k)
{
  if (a<=0)
    a=1;
  else
    if (a>12)
      a=12;
  if (b>8)
    b=8;
  else
    if (b<0)
      b=0;

  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: SetGenes\n";
  ofs << "Gene values: " << a << " " << b << " " << c << " "
                         << d << " " << e << " " << f << " "
                         << g << " " << h << " " << i << " "
                         << j << " " << k << "\n\n";
  ofs.close();
  #endif

  genes[0]=a;		// Number of offspring
  genes[1]=b;		// Number of iterations
  genes[2]=c;		// Length of first line
  genes[3]=d;		// Length of second line
  genes[4]=e;		// Offshoot point
  genes[5]=f;		// First angle
  genes[6]=g;		// Second angle
  genes[7]=h;		// Length of trunk

  // If we're using colors, set the new values

  if (useColors)
    {
      genes[8]=i;		// Red
      genes[9]=j;		// Green
      genes[10]=k; 	// Blue
    }

  // .. otherwise, make sure the biomorph is black.

  else
    {
      genes[8]=0;		// Red
      genes[9]=0;		// Green
      genes[10]=0; 	// Blue
    }

  // Perform range checking on color values.

  for (int a=8;a!=11;a++)
    {
      if (genes[a]<0)
        genes[a]=0;
      if (genes[a]>255)
        genes[a]=255;
    }
}

//==================================
// SetXY
//
// This method sets the new X and Y coordinates for
// the biomorph to be drawn onto the screen
//
// Receives: New X and Y coords
//  Returns: Nothing
//==================================

void TBiomorph::SetXY(int newx, int newy)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: SetXY\n";
  ofs << "New co-ords: ("<<newx<<","<<newy<<")\n\n";
  ofs.close();
  #endif
  xoff=newx;
  yoff=newy;
}

//==================================
// Display
//
// This routine takes a TClientDC object and uses it to
// call the internal biomoprh draw routine
//
// Receives: TClientDC object and erase/draw boolean flag
//           If erase flag is TRUE then the biomorph will
//           be drawn using the background color and thus
//           "erased"
//  Returns: Nothing
//==================================

void TBiomorph::Display(TClientDC &dc, bool erase)
{

  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: Display\n\n";
  ofs.close();
  #endif

  // Create the pen. If erasing the biomorph, select
  // a pen with the background color.

  TPen *myPen;
  if (erase)
    myPen = new TPen(TColor(red,green,blue), 1, PS_SOLID);
  else
    myPen = new TPen(TColor(genes[8],genes[9],genes[10]),1,PS_SOLID);

  // Draw the trunk

  dc.SelectObject(*myPen);
  dc.MoveTo(xoff+60,yoff+60);
  dc.LineTo(xoff+60,yoff+60-genes[7]);
  drawAngle=18.9;
  int count=0;

  // Draw the UPWARD segments

  for (count=0;count!=2;count++)
    Draw(dc,genes[1],xoff+60,yoff+60-genes[7]-count*5,drawAngle);

  // Draw the LEFTWARD segments

  drawAngle=9.3;
  count=0;
  for (count=0;count!=2;count++)
    Draw(dc,genes[1],xoff+60-(count*5),yoff+60-genes[7],drawAngle);

  // Draw the RIGHTWARD segments

  drawAngle=28.3;
  count=0;
  for (count=0;count!=2;count++)
    Draw(dc,genes[1],xoff+60+(count*5),yoff+60-genes[7],drawAngle);

  // Draw the DOWNWARD segments

  drawAngle=37.6;
  count=0;
  for (count=0;count!=2;count++)
    Draw(dc,genes[1],xoff+60,yoff+60-genes[7]+(count*5),drawAngle);
  dc.RestorePen();

  delete myPen;
}

//==================================
// Draw
//
// This is the internal draw routine used to actually draw
// the biomorph on the screen. It is called by the
// Display method
//
// Receives: TClientDC object, iteration count, x and y
//           co-ordinates and intial line angle from the trunk
//           of the biomorph
//  Returns: Nothing
//==================================

void TBiomorph::Draw(TClientDC &dc, int count, int x, int y, float rotation)
{
  if (count!=0)
    {
      count--;
      int length=0;

      // If this iteration number is EVEN, then take gene 2
      // as the length of this line. Otherwise, use gene 3.

      if (IsEven(count))
        length = genes[2];
      else
        length = genes[3];

      // The main branch on the left

      dc.MoveTo(x,y);
      int newx = x - length * sin (rotation/M_2PI);
      int newy = y + length * cos (rotation/M_2PI);
      dc.LineTo(newx, newy);

      // The "offshoot" branch on the left

      newx = x - (((float)length/100)*genes[4]) * sin (rotation/M_2PI);
      newy = y + (((float)length/100)*genes[4]) * cos (rotation/M_2PI);
      dc.MoveTo(newx, newy);
      newx = x - length * sin ((drawAngle-genes[6])/M_2PI);
      newy = y + length * cos ((drawAngle-genes[6])/M_2PI);
      dc.LineTo(newx, newy);
      Draw(dc,count,newx,newy, rotation-genes[5]);

      // The main branch on the right

      dc.MoveTo(x,y);
      newx = x - length * sin (rotation/M_2PI);
      newy = y + length * cos (rotation/M_2PI);
      dc.LineTo(newx, newy);

      // The "offshoot" branch on the right

      newx = x - (((float)length/100)*genes[4]) * sin (rotation/M_2PI);
      newy = y + (((float)length/100)*genes[4]) * cos (rotation/M_2PI);
      dc.MoveTo(newx, newy);
      newx = x - length * sin ((drawAngle+genes[6])/M_2PI);
      newy = y + length * cos ((drawAngle+genes[6])/M_2PI);
      dc.LineTo(newx, newy);

      Draw(dc,count,newx,newy, rotation+genes[5]);
    }
}

//==================================
// Mutate
//
// This routine will randomly choose a gene to alter in this
// biomorph. All range checking for this function is done
// internally and no wrapping is provided - that is to say,
// once a gene value exceeds its maximum, the maximum value is
// then used, rather than wrapping back around to the minimum.
//
// Receives: Nothing
//  Returns: Nothing
//==================================

int TBiomorph::Mutate()
{
  int geneNumber=random(11);
  int pos_or_neg=random(100);

  // If the number of offspring (gene 0) is being altered, increase it
  // or decrease by 1. Otherwise, add or subtract 2 from the gene value.
  // This was done to increase the rate of change in each of the new
  // offspring biomorphs, as the process turned out to be very slow.

  if (geneNumber!=0)
    {
      if (pos_or_neg>50)
        genes[geneNumber]+=2;
      else
        genes[geneNumber]-=2;
    }
  else
    {
      if (pos_or_neg>50)
        genes[geneNumber]++;
      else
        genes[geneNumber]--;
    }

  // If the gene mutating is a color gene AND
  // we're using colors, make the color change more pronounced.

  if ((geneNumber>7)&&(useColors))
    {
      if (pos_or_neg>50)
        genes[geneNumber]+=20;
      else
        genes[geneNumber]-=20;
    }

  // Perform some range testing

  if (genes[geneNumber]<0)
    genes[geneNumber]=1;
  if (genes[1]>8)
    genes[1]=8;
  if (genes[0]>12)
    genes[0]=12;
  if (genes[0]<=0)
    genes[0]=1;

  // Range check the color genes

  for (int i=8;i!=11;i++)
    {
      if (genes[i]>255)
        genes[i]=255;
      if (genes[i]<0)
        genes[i]=0;
    }

  // If no colors are being used, set red, green and blue to 0.

  if (!useColors)
    for (int a=8;a!=11;a++)
      genes[a]=0;

  // Return the gene number we just changed, for statistics
  // purposes.
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: Mutate\n";
  ofs << "Gene changed: " << geneNumber << "\n\n";
  ofs.close();
  #endif

  return geneNumber;
};

//==================================
// SetGene
//
// Set a particular gene value given an index
//
// Receives: Index, new gene value
//  Returns: Nothing
//==================================

void TBiomorph::SetGene(int index, int value)
{
  genes[index]=value;

  // If the changed gene was a color but we're not using color
  // make sure the color remains black

  if ((index>7)&&(!useColors))
    genes[index]=0;
};

//==================================
// GetGenes
//
// Gets all the gene values for this biomorph
//
// Receives: Addresses to store all gene values into
//  Returns: Nothing
//==================================

void TBiomorph::GetGenes
(int&a,int&b,int&c,int&d,int&e,int&f,int&g,int&h,int&i,int&j,int&k)
{
  a=genes[0];
  b=genes[1];
  c=genes[2];
  d=genes[3];
  e=genes[4];
  f=genes[5];
  g=genes[6];
  h=genes[7];
  i=genes[8];
  j=genes[9];
  k=genes[10];
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TBIOMORPH ***\n";
  ofs << "Method called: GetGenes\n";
  ofs << "Gene values: " << a << " " << b << " " << c << " "
                         << d << " " << e << " " << f << " "
                         << g << " " << h << " " << i << " "
                         << j << " " << k << "\n\n";
  ofs.close();
  #endif
}

