#include <iostream.h>
#include "theArray.h"

theArray MyArray;

main (void)
{
  cout << "This is in Main!\n";
  delete[] theArray;
  return 0;
}