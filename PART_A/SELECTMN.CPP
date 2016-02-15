// selectionManager class

// By Simon Mitchell		96878291

// 27/3/98

// This is the manager for the Object Orientated prototype of Part A
// of the BIOMORPHS programming assignment.
// The manager handles the two text container objects used in the
// evolution process:

// oriArray  -  the original text entered or loaded
// evoArray  -  array used to store evolving text under natural selection

#include<iostream.h>
#include<stdlib.h>
#include<stddef.h>
#include<fstream.h>
#include<time.h>
#include"selectmn.h"
#include"limits.h"
#include"interfac.h"

//----------------------------------------
// CONSTRUCTOR
//----------------------------------------

selectionManager::selectionManager()
{
  randomize();
}

//----------------------------------------
// DESCTRUCTOR
//----------------------------------------

selectionManager::~selectionManager(){}

//----------------------------------------
// run
//
// Begins execution of the selection manager. Typically called from
// mainLine.
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void selectionManager::run()
{
  int choice=0;
  while (choice!=3)
  {

// Remove all old information from both the arrays.

	 oriArray.emptyArray();
	 evoArray.emptyArray();

// Menu and options

	 myInterface.showMenu();
	 myInterface.getChoice(choice);
	 switch(choice)
	  {
		 case 1  :  keyboardText();
						break;
		 case 2  :  fileText();
						break;
		 case 3  :  cout << "Exiting program ...\n";
						break;
		 default :  cerr << "Invalid selection, please try again\n";
						break;
	  }
  }
}

//----------------------------------------
// keyboardText
//
// Retrieves text to be evolved, from the keyboard.
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void selectionManager::keyboardText()
{
  char *buffer, *outfile, choice;
  int count=0;
  int saveReport=0;
  buffer = new char[100];
  outfile = new char[100];

  cout << "Should I generate a report file (y/n)? *>";
  cin >> choice;
  if (choice=='y')
	 {
		cin.clear();
		cin.ignore(90,'\n');
		cout << "Please enter the filename or leave blank to cancel.\n";
		cin.getline(outfile,100);
		if (cin.gcount()==1)
		  saveReport=0;
		else
		  saveReport=1;
	 }
  cout << "\nEnter some text. Enter \".\" on a line by it's own, to start\n";
  cout << "the evolution process\n";
  cin.getline(buffer,100);
  count=cin.gcount();
  count--;
  int i=0;

  oriArray.resetPtr();

  if (buffer[0]!='.')
	 {
		while (buffer[0]!='.')
		  {
			 for (i=0;i!=count;i++)
				oriArray.addToArray(buffer[i]);
			 oriArray.addToArray('\n');
			 cin.getline(buffer,100);
			 count=cin.gcount();
			 count--;
		  }

		fillEvoArray();
		evolve();
		if (saveReport)
		  writeReport(outfile);
	 }
  else
	 cout << "\n\nNo text to evolve was entered!\n\n";
  delete[] buffer;
}

//----------------------------------------
// file Text
//
// Retrieves text to be evolved, from disk
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void selectionManager::fileText()
{

// Filenames

  char *filename, *outfile;

// Char input buffer

  char bufferchar;

// Var used to remember whether user wants a report file generated

  int saveReport=0;
  int count=0;
  filename = new char[100];
  outfile = new char[100];
  cout << "Should I generate a report file (y/n)? *>";
  cin >> bufferchar;
  if (bufferchar=='y')
	 saveReport=1;
  cin.clear();
  cin.ignore(90,'\n');
  cout << "Please enter the filename of the text to load in or leave blank to cancel.\n";
  cin.getline(filename,100);

// Generate the report file name. Chop off the end extention, and add the
// .out to the original text file name.

  if (filename[count]!=NULL)
	 {
		while (filename[count]!='.')
		  {
			 outfile[count]=filename[count];
			 count++;
		  }
		outfile[count++]='.';
		outfile[count++]='o';
		outfile[count++]='u';
		outfile[count++]='t';
		outfile[count]=NULL;

		if (cin.gcount()!=0)
		  {
			 fstream inFile(filename,ios::in);
			 if (inFile.fail())
				cerr << "Could not open file " << filename << " for input!\n";
			 else
				{
				  oriArray.resetPtr();
				  while (!inFile.eof())
					 {
						inFile.read((char *) &bufferchar, sizeof(bufferchar));
						if ((bufferchar<32)||(bufferchar>126))
						  bufferchar='\n';
						oriArray.addToArray(bufferchar);
					 }
				  inFile.close();
				  fillEvoArray();
				  evolve();
				  if (saveReport)
					 writeReport(outfile);
				}
		  }
  }
  else
	 cout << "\n\nCancelled, at users request.\n\n";
}

//----------------------------------------
// fillEvoArray
//
// Fills the evoArray with the same number of chars as oriArray contains.
// Note that all the chars used to fill it are chosen RANDOMLY.
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void selectionManager::fillEvoArray()
{
  int count=0;
  count=oriArray.numElements();
  int value=0;
  while (count!=0)
  {
	 value=getRandom();
	 evoArray.addToArray(value);
	 count--;
  }
}

//----------------------------------------
// evolve
//
// This method handles the evolution under natural selection phase.
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void selectionManager::evolve()
{
  int count=0;
  int i=0;
  char choice;
  int fullDetails=0;
  cout <<"\nShall I display full details on the screen, during evolution (y/n)? *>";
  cin >> choice;
  if (choice=='y')
	 fullDetails=1;
  cin.clear();
  cin.ignore(90,'\n');
  generations=0;
  count=oriArray.numElements();

  int finished=0;
  int maxcount =0;
  start =0;
  end=0;
  char oriChar, evoChar;

  while (finished==0)
  {

	 // MAXCOUNT here is used to determine how many characters were
	 // changed in the RESULT array.
	 // If MAXCOUNT == COUNT, then we changed them all, and we're not
	 // finished. If MAXCOUNT==0, nothing was changed and we can exit.

	 maxcount=0;
	 oriChar=evoChar=' ';
	 oriArray.resetPtr();
	 evoArray.resetPtr();
	 start=clock();
	 i=0;
	 for (i=0;i!=count;i++)
		{
		  evoChar=evoArray.getNext();
		  oriChar=oriArray.getNext();
		  if (evoChar!=oriChar)
			 {
				evoArray.setCurrent(getRandom());
				maxcount++;
			 }
		  evoArray.advancePtr();
		  oriArray.advancePtr();
		}
	 end=clock();
	 diff=end-start;
	 if(diff>maxTime)
		maxTime=diff;
	 if(diff<minTime)
		minTime=diff;

	 generations++;

    cout << "\n**********\nGeneration: " <<generations << "\n\n";

	 if (fullDetails)
      evoArray.contentsOfArray();

	 if (maxcount==0)
		finished=1;
  }
  mean=((maxTime-minTime)/2);
  cout << "\nFINISHED!\n";
  cout << "         This took " << generations << " generations to complete!\n";
  cout << " Longest cycle was " << maxTime << "ticks\n";
  cout << "Shortest cycle was " << minTime << "ticks\n";
  cout << "    Mean cycle was " << mean << "ticks\n";
}

//----------------------------------------
// writeReport
//
// Receives: Filename for report file
//  Returns: Nothing
//----------------------------------------

void selectionManager::writeReport(char *reportFile)
{
  cout << "\nGenerating report file ... \n";
  fstream outfile;
  outfile.open(reportFile,ios::out);
  if (!outfile)
	 {
		cerr << "*** ERROR: Could not create file " << reportFile<< " for output! ***\n";
	 }
  else
	 {
		outfile << "REPORT ON EVOLUTION BY NATURAL SELECTION!\n";
		outfile << "------ -- --------- -- ------- ----------\n\n";
		outfile << "Number of generations needed: " << generations << "\n\n";
		outfile << "\nTime taken on natural selection routine.\n\n";
		outfile << "    Mean time needed: " << mean << "\n";
		outfile << "Maxmimum time needed: " << maxTime << "\n";
		outfile << " Minimum time needed: " << minTime << "\n";
	 }
  outfile.close();
}

//----------------------------------------
// getRandom
//
// Receives: Nothing
//  Returns: Random integer

// NOTE!!!!!!!
// AScii code 127 is used to represent a carraige return.
// This simplifies things a little, since /n has a value of 13,
// below the first "printable" character that can be used - space or 32.
//----------------------------------------

int selectionManager::getRandom()
{
  int myValue;
  myValue=random(96)+32;
  if (myValue==127)
	 myValue='\n';
  return myValue;
}

