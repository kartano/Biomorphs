// INTERFACE class

// By Simon Mitchell				96878291

// 29/3/98

// This class provides a menu interface for the natural selection manager.

#include<limits.h>
#include"interfac.h"

//-----------------------------------------
// CONSTRUCTOR
//----------------------------------------

interface::interface(){};

//-----------------------------------------
// DESTRUCTOR
//----------------------------------------

interface::~interface(){};

//-----------------------------------------
// getChoice
//
// Gets valid integer, handles illegal input
//
// Receives: Address of a choice variable
//  Returns: Valid integer BY REFERRENCE to choice
//----------------------------------------

void interface::getChoice(int &choice)
{
  cin >> choice;
  while (!cin.eof()&&cin.fail())
  {
	 cerr << "Invalid value, please enter another selection.\n";
	 cin.clear();
	 cin.ignore(INT_MAX,'\n');
	 cin >> choice;
  }
  cin.clear();
  cin.ignore(INT_MAX,'\n');
}

//-----------------------------------------
// showMenu
//
// Displays main menu options
//
// Receives: Nothing
//  Returns: Nothing
//----------------------------------------

void interface::showMenu()
{
	 cout << "Please selection an option ....\n\n";
	 cout << "1)\tEnter text from the keyboard\n";
	 cout << "2)\tLoad in a text file from disk\n\n";
	 cout << "3)\tQUIT THE PROGRAM\n";
}

