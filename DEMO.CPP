// "Natural selection" process with a single line of text
// By Simon Mitchell  (96878291)
// 19/3/98

// This program will accept a small line of text, and apply the idea
// of "natural selection" to it, as described in Part A of the
// "BIOMORPHS" major project description.

// Just to get a "working" idea on screen in text mode, since I cannot
// get OWL to work on my current version of C++ (4.5 under Win95).

// FILES:	demo.cpp		-	Source code

#include<iostream.h>
#include<stdlib.h>
#include<stddef.h>

// #define debugging				// Debugging switch

int i=0, generations=1;

main (void)
{
  char *name, *result;
  int buf_size=100;
  int count=0;

  name = new char[buf_size];
  result = new char[buf_size];

  randomize();

  cout << "Please enter some text!\n";
  cin.getline(name,buf_size);
  count=cin.gcount();
  count--;

  int finished=0;
  int maxcount =0;

  while (finished==0)
  {
	 #ifdef debugging
	 cout << "*** At start of WHILE loop\n";
	 cout << "*** Finished = " << finished << "\n";
	 #endif

	 // MAXCOUNT here is used to determine how many characters were
	 // changed in the RESULT array.
	 // If MAXCOUNT == COUNT, then we changed them all, and we're not
	 // finished. If MAXCOUNT==0, nothing was changed and we can exit.

	 maxcount=0;
	 for (i=0;i!=count;i++)
		{
		  if (result[i]!=name[i])
			 {
				#ifdef debugging
				cout << "*** Chars don't match.\n";
				cout << "*** Result["<<i<<"] = " << result[i] << "\n";
				cout << "***   Name["<<i<<"] = " << name[i] << "\n";
				#endif
				result[i]=random(96)+32;
				maxcount++;
			 }
		}
	 for (i=0;i!=count;i++)
		cout << result[i];
	 cout << "\n";

	 #ifdef debugging
	 cout << "*** Maxcount = " << maxcount << "\n";
	 cout << "***   Count = " << count << "\n";
	 #endif

	 generations++;

	 if (maxcount==0)
	 {
		finished=1;
		cout << "\nFINISHED!\n";
		cout << "This took " << generations << " generations to complete!\n";
	 }

	 #ifdef debugging
	 cout << "*** At end of WHILE loop.\n";
	 cout << "*** Finished = " << finished << "\n";
	 #endif
  }

  delete[] name;
  delete[] result;

  return 0;
}


