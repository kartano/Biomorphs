// interface class INTERFACE

// By Simon Mitchell				96878291

// 29/3/98

#include<iostream.h>

#ifndef INTERFACE_CLASS
#define INTERFACE_CLASS

class interface {

public:

  interface();
  ~interface();
  void getChoice(int&);
  void showMenu();
};

#endif