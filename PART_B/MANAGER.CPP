/*======================================
TManager IMPLEMENTATION

By Simon Mitchell (96878291)

BASE CLASSES: None
======================================*/

#include "manager.h"

//====================================
// CONSTRUCTOR
//====================================

TManager::TManager(bool flag, int R, int G, int B)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: Contructor\n\n";
  ofs.close();
  #endif

  morph1 = new TBiomorph(flag, R,G,B, 0,0);
  morph2 = new TBiomorph(flag, R,G,B, 0,0);
  morph3 = new TBiomorph(flag, R,G,B, 0,0);
  morph4 = new TBiomorph(flag, R,G,B, 0,0);

  morph5 = new TBiomorph(flag, R,G,B, 0,0);
  morph6 = new TBiomorph(flag, R,G,B, 0,0);

  morph7 = new TBiomorph(flag, R,G,B, 0,0);
  morph8 = new TBiomorph(flag, R,G,B, 0,0);

  morph9 = new TBiomorph(flag, R,G,B, 0,0);
  morph10 = new TBiomorph(flag, R,G,B, 0,0);
  morph11 = new TBiomorph(flag, R,G,B, 0,0);
  morph12 = new TBiomorph(flag, R,G,B, 0,0);

  parent  = new TBiomorph(flag, R,G,B,205,165);

  ResetBiomorphs();
};

//====================================
// DESTRUCTOR
//====================================

TManager::~TManager()
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: Destructor\n";
  #endif
  delete morph1;
  delete morph2;
  delete morph3;
  delete morph4;

  delete morph5;
  delete morph6;

  delete morph7;
  delete morph8;

  delete morph9;
  delete morph10;
  delete morph11;
  delete morph12;

  delete parent;

  #ifdef DEBUG
  ofs << "morph1 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph2 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph3 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph4 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph5 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph6 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph7 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph8 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph9 of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph10 of type TBiomorph deleted: " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph11 of type TBiomorph deleted: " << sizeof(TBiomorph) << " bytes\n";
  ofs << "morph12 of type TBiomorph deleted: " << sizeof(TBiomorph) << " bytes\n";
  ofs << "parent of type TBiomorph deleted:  " << sizeof(TBiomorph) << " bytes\n\n";
  ofs.close();
  #endif
};

//====================================
// ResetBiomorphs
//
// Resets all biomorphs to their original values.
// It also sets the number of offspring to 12 and sets all
// the boxes to "active" status and resets all the changed gene values.
//
// Receives: Nothing
//  Returns: Nothing
//====================================

void TManager::ResetBiomorphs()
{
  for (int i=0;i!=12;i++)
    active[i]=true;
  for (int i=0;i!=11;i++)
    geneChanges[i]=0;

  int va = random(5)+1;
  parent->SetGenes(0,0,0,0,0,0,0,0,0,0,0);
  morph1->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph2->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph3->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph4->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph5->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph6->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph7->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph8->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph9->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph10->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph11->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
  va = random(5)+1;
  morph12->SetGenes(6,va,va,va,va,va,va,va,0,0,0);
};

//====================================
// SetColors
//
// Adjusts the "useColors" flag for each of the biomorphs.
//
// Receives: Erase flag
//  Returns: Nothing
//====================================

void TManager::SetColors(bool flag)
{
  morph1->UseColors(flag);
  morph2->UseColors(flag);
  morph3->UseColors(flag);
  morph4->UseColors(flag);
  morph5->UseColors(flag);
  morph6->UseColors(flag);
  morph7->UseColors(flag);
  morph8->UseColors(flag);
  morph9->UseColors(flag);
  morph10->UseColors(flag);
  morph11->UseColors(flag);
  morph12->UseColors(flag);
  parent->UseColors(flag);
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: SetColors\n\n";
  ofs << "useColors flag value is now: ";
  (flag) ? ofs << "TRUE\n\n" : ofs << "FALSE\n\n";
  ofs.close();
  #endif
}

//====================================
// SetRegion
//
// This method sets the coordinates for a particular box
// which would contain a biomorph offspring. It then also
// sets the X and Y values for the appropriate Biomorph.
//
// Receives: Index, set of rectangle coordinates
//  Returns: Nothing
//====================================

void TManager::SetRegion(int index, int x1, int y1, int x2, int y2)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: SetRegion\n";
  ofs << "Morph number: " << index << "\n";
  ofs << "Region:        ("<<x1<< "," << y1 << "," << x2 << "," << y2 << ")\n\n";
  ofs.close();
  #endif
  boxes[index][0]=x1;
  boxes[index][1]=y1;
  boxes[index][2]=x2;
  boxes[index][3]=y2;
  switch(index)
    {
      case 0 : morph1->SetXY(x1,y1);
               break;
      case 1 : morph2->SetXY(x1,y1);
               break;
      case 2 : morph3->SetXY(x1,y1);
               break;
      case 3 : morph4->SetXY(x1,y1);
               break;
      case 4 : morph5->SetXY(x1,y1);
               break;
      case 5 : morph6->SetXY(x1,y1);
               break;
      case 6 : morph7->SetXY(x1,y1);
               break;
      case 7 : morph8->SetXY(x1,y1);
               break;
      case 8 : morph9->SetXY(x1,y1);
               break;
      case 9 : morph10->SetXY(x1,y1);
               break;
      case 10: morph11->SetXY(x1,y1);
               break;
      case 11: morph12->SetXY(x1,y1);
               break;
    }
}

//====================================
// SetParent
//
// This method alters the genes of the parent biomorph.
// It copies the genes within the selected offspring biomorph
// across to the parent. It then activates the appropriate
// number of offspring (relative to gene 0 of the new parent)
// and causes the new offspring to mutant.
//
// Receives: Client device context object, index of new parent,
//           flag for "max offspring" setting
//  Returns: Nothing
//====================================

void TManager::SetParent(TClientDC &dc, int index, bool maxOffspring)
{

  // Copy the new gene pattern into the parent.

  int i=0;
  if (maxOffspring)
   {
      morph1->SetGene(0,12);
      morph2->SetGene(0,12);
      morph3->SetGene(0,12);
      morph4->SetGene(0,12);
      morph5->SetGene(0,12);
      morph6->SetGene(0,12);
      morph7->SetGene(0,12);
      morph8->SetGene(0,12);
      morph9->SetGene(0,12);
      morph10->SetGene(0,12);
      morph11->SetGene(0,12);
      morph12->SetGene(0,12);
    }

  if (active[index])
   {
    #ifdef DEBUG
    ofstream ofs(DEBUG_FILE,ios::app);
    ofs << "*** INSIDE TMANAGER ***\n";
    ofs << "Method called: SetParent\n";
    ofs << "New parent morph number: " << index << "\n\n";
    ofs.close();
    #endif
    parent->Display(dc,true);
    switch (index)
      {
        case 0 : for (i=0;i!=11;i++) parent->SetGene(i,morph1->GetGene(i));
                 break;
        case 1 : for (i=0;i!=11;i++) parent->SetGene(i,morph2->GetGene(i));
                 break;
        case 2 : for (i=0;i!=11;i++) parent->SetGene(i,morph3->GetGene(i));
                 break;
        case 3 : for (i=0;i!=11;i++) parent->SetGene(i,morph4->GetGene(i));
                 break;

        case 4 : for (i=0;i!=11;i++) parent->SetGene(i,morph5->GetGene(i));
                 break;
        case 5 : for (i=0;i!=11;i++) parent->SetGene(i,morph6->GetGene(i));
                 break;

        case 6 : for (i=0;i!=11;i++) parent->SetGene(i,morph7->GetGene(i));
                 break;
        case 7 : for (i=0;i!=11;i++) parent->SetGene(i,morph8->GetGene(i));
                 break;

        case 8 : for (i=0;i!=11;i++) parent->SetGene(i,morph9->GetGene(i));
                 break;
        case 9 : for (i=0;i!=11;i++) parent->SetGene(i,morph10->GetGene(i));
                 break;
        case 10: for (i=0;i!=11;i++) parent->SetGene(i,morph11->GetGene(i));
                 break;
        case 11: for (i=0;i!=11;i++) parent->SetGene(i,morph12->GetGene(i));
                 break;
      }

    // Make sure only the right number of offspring are
    // now active.

    for (int i=0;i!=12;i++)
      active[i]=false;
    for (int i=0;i!=parent->GetGene(0);i++)
      active[i]=true;

    // Copy the new parent's gene patterns into each of the
    // active offspring

    for(int a=0;a!=11;a++)
      {
         morph1->SetGene(a,parent->GetGene(a));
         morph2->SetGene(a,parent->GetGene(a));
         morph3->SetGene(a,parent->GetGene(a));
         morph4->SetGene(a,parent->GetGene(a));
         morph5->SetGene(a,parent->GetGene(a));
         morph6->SetGene(a,parent->GetGene(a));
         morph7->SetGene(a,parent->GetGene(a));
         morph8->SetGene(a,parent->GetGene(a));
         morph9->SetGene(a,parent->GetGene(a));
         morph10->SetGene(a,parent->GetGene(a));
         morph11->SetGene(a,parent->GetGene(a));
         morph12->SetGene(a,parent->GetGene(a));
      }

    // Then mutate all active offspring.

    if (active[0]) geneChanges[morph1->Mutate()]++;
    if (active[1]) geneChanges[morph2->Mutate()]++;
    if (active[2]) geneChanges[morph3->Mutate()]++;
    if (active[3]) geneChanges[morph4->Mutate()]++;
    if (active[4]) geneChanges[morph5->Mutate()]++;
    if (active[5]) geneChanges[morph6->Mutate()]++;
    if (active[6]) geneChanges[morph7->Mutate()]++;
    if (active[7]) geneChanges[morph8->Mutate()]++;
    if (active[8]) geneChanges[morph9->Mutate()]++;
    if (active[9]) geneChanges[morph10->Mutate()]++;
    if (active[10]) geneChanges[morph11->Mutate()]++;
    if (active[11]) geneChanges[morph12->Mutate()]++;
   }
}

//====================================
// SetParentGenes
//
// This method directly alters the gene patterns of a parent.
// This is done indirectly by copying the genes into morph 0
// and then selecting this as the new parent. By doing this
// the program forces a new generation of offspring whenever
// the program directly alters the parent
//
// Receives: Client device context object, 11 new gene values
//  Returns: Nothing
//====================================

void TManager::SetParentGenes(TClientDC &newDc, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k)
{
  morph1->Display(newDc, true);
  morph1->SetGenes(a,b,c,d,e,f,g,h,i,j,k);
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: SetParentGenes\n";
  ofs << "Gene values: " << a << " " << b << " " << c << " "
                         << d << " " << e << " " << f << " "
                         << g << " " << h << " " << i << " "
                         << j << " " << k << "\n\n";
  ofs.close();
  #endif
}

//====================================
// GetParent
//
// This method returns (by REFERRENCE) the gene values for
// the current parent.
//
// Receives: Addresses of integers for gene values
//  Returns: Nothing
//====================================

void TManager::GetParent
(int &a, int &b, int &c, int &d, int &e, int &f, int &g, int &h, int &i, int &j, int &k)
{
  a=parent->GetGene(0);
  b=parent->GetGene(1);
  c=parent->GetGene(2);
  d=parent->GetGene(3);
  e=parent->GetGene(4);
  f=parent->GetGene(5);
  g=parent->GetGene(6);
  h=parent->GetGene(7);
  i=parent->GetGene(8);
  j=parent->GetGene(9);
  k=parent->GetGene(10);
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: GetParent\n";
  ofs << "Gene values: " << a << " " << b << " " << c << " "
                         << d << " " << e << " " << f << " "
                         << g << " " << h << " " << i << " "
                         << j << " " << k << "\n\n";
  ofs.close();
  #endif

}

//====================================
// Draw
//
// This method will draw all the active bimorphs
//
// Receives: Client device context, erase flag
//  Returns: Nothing
//====================================

void TManager::Draw(TClientDC &dc, bool erase)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: Draw\n\n";
  ofs.close();
  #endif
  if (active[0]) morph1->Display(dc, erase);
  if (active[1]) morph2->Display(dc, erase);
  if (active[2]) morph3->Display(dc, erase);
  if (active[3]) morph4->Display(dc, erase);

  if (active[4]) morph5->Display(dc, erase);
  if (active[5]) morph6->Display(dc, erase);

  if (active[6]) morph7->Display(dc, erase);
  if (active[7]) morph8->Display(dc, erase);

  if (active[8]) morph9->Display(dc, erase);
  if (active[9]) morph10->Display(dc, erase);
  if (active[10]) morph11->Display(dc, erase);
  if (active[11]) morph12->Display(dc, erase);

  parent->Display(dc,erase);
};

//====================================
// GetStats
//
// This method will return the number of times each of
// the 11 genes have changed.
//
// Receives: Addresses of integers to store statistics result into
//  Returns: Nothing
//====================================

void TManager::GetStats(int &a,int &b,int &c,int &d,int &e,int &f,int &g,int &h,int &i,int &j,int &k)
{
  a=geneChanges[0];
  b=geneChanges[1];
  c=geneChanges[2];
  d=geneChanges[3];
  e=geneChanges[4];
  f=geneChanges[5];
  g=geneChanges[6];
  h=geneChanges[7];
  i=geneChanges[8];
  j=geneChanges[9];
  k=geneChanges[10];
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: GetStats\n";
  ofs << "Change values: " << a << " " << b << " " << c << " "
                           << d << " " << e << " " << f << " "
                           << g << " " << h << " " << i << " "
                           << j << " " << k << "\n\n";
  ofs.close();
  #endif

};

//====================================
// GetMorph
//
// This method returns all the gene values for a particular
// biomorph, by index.
//
// Receives: Index, addresses of integers to store gene values into
//  Returns: Nothing
//====================================

void TManager::GetMorph(int index,
int&a, int&b, int&c, int&d, int&e, int&f, int&g, int&h, int&i, int&j, int&k)
{
  switch (index)
    {
      case 0 : morph1->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 1 : morph2->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 2 : morph3->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 3 : morph4->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 4 : morph5->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 5 : morph6->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 6 : morph7->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 7 : morph8->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 8 : morph9->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 9 : morph10->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
               break;
      case 10 : morph11->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
                break;
      case 11 : morph12->GetGenes(a,b,c,d,e,f,g,h,i,j,k);
                break;
      default : a=b=c=d=e=f=g=h=i=j=k=0;
                break;
    }
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: GetMorph\n";
  ofs << "Morph chosen: " << index << "\n";
  ofs << "Gene values:  " << a << " " << b << " " << c << " "
                          << d << " " << e << " " << f << " "
                          << g << " " << h << " " << i << " "
                          << j << " " << k << "\n\n";
  ofs.close();
  #endif

}

//====================================
// SetParentGene
//
// This method allows a particular gene in the current parent to
// be set.
//
// Receives: Gene number index and new gene value
//  Returns: Nothing
//====================================

void TManager::SetParentGene(int index, int value)
{
  #ifdef DEBUG
  ofstream ofs(DEBUG_FILE,ios::app);
  ofs << "*** INSIDE TMANAGER ***\n";
  ofs << "Method called: SetParentGene\n";
  ofs << "Gene chosen: " << index << "\n";
  ofs << "New value:   " << value << "\n\n";
  ofs.close();
  #endif
  parent->SetGene(index,value);
}

