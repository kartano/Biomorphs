@echo off
cls
a:
cd\
mkdir part_a
c:

echo "COPYING PART_A FILES..."
copy part_a.h a:\part_a
copy part_a.cpp a:\part_a
copy part_a.exe a:\part_a

echo "COPYING ANARRAY ADS FILES..."
copy anarray.h a:\part_a
copy anarray.cpp a:\part_a

echo "COPYING EVOLUTION MANAGER FILES..."
copy evolve.h a:\part_a
copy evolve.cpp a:\part_a

echo "COPYING RESOURCE HEADER..."
copy resource.rh a:\part_a

echo "COPYING SETUP DIALOG FILES..."
copy setupdia.h a:\part_a
copy setupdia.cpp a:\part_a

echo "COPYING EDIT EXAMPLE FILES..."
copy editexam.h a:\part_a
copy editexam.cpp a:\part_a

echo "COPYING EXAMPLE TEXT TEST FILE..."
copy test.txt a:\part_a

echo "COPYING RESOURCE SCRIPT..."
copy part_a.rc a:\part_a

echo "COPYING REPORT DIALOG FILES..."
copy repdia.h a:\part_a
copy repdia.cpp a:\part_a

echo "COPYING WAIT-CURSOR FILES..."
copy waitcurs.h a:\part_a
copy waitcurs.cpp a:\part_a

echo "*** COPYING COMPLETE ***"
