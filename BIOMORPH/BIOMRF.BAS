CLS

print"ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»"
print"º                                                                           º"
print"º                                 BIOMURFFS                                 º"
print"º                                 ÄÄÄÄÄÄÄÄÄ                                 º"
print"º                                                                           º"
print"º                                VERSION 1.3                                º"
print"º                                                                           º"
print"º                                D.J. Murphy                                º"
print"º                               12th May 1988                               º"
print"ÇÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¶"
print"º                                                                           º"
print"º                                                                           º"
print"º This program is based  on the one  Richard Dawkins  describes in his book º"
print"º 'The Blind Watchmaker'. If you want to know  what each bit does, read the º"
print"º file  'BIO.DOC'  which will  describe  how  the data is  coded and  used. º"
print"º If, however, you just want to see  the computer drawing  pretty patterns, º"
print"º the questions you are  asked in the program are self explanatory once you º"
print"º get going. In order to get the hang of it, use the default starting genes º"
print"º which    means    replying   N   to    the    second    two    questions. º"
print"º                                                                           º"
print"ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼"


' Subroutine MAIN
' This is the main segment of the biomurff program, controlling the operation
' of the other routines

option base 1

dim biomorphs%(16,9), posns%(2048,4)

locate 23,3
input"Do you have a printer connected ";reply$
if ucase$(left$(reply$,1)) = "Y" then shell "graphics"

locate 23,3
input"Do you want to define the initial gene values yourself ";reply$
cls
screen 2
if ucase$(left$(reply$,1)) = "Y" then

	print"The genes control biomorph phenotypes as follows:"
        print
	print"1: # of offspring"
	print"2: # of iterations in drawing"
	print"3: branch length 1"
	print"4: branch length 2"
	print"5: branch length combination"
	print"6: angle (degrees) of 1st branch from stem"
	print"7: angle (degrees) of 2nd branch from 1st"
	print"8: length of initial branch"
        print

	for bio% = 1 to 8
		print"Gene ";bio%;
		input" Value ";biomorphs%(1,bio%)
	next bio%

else

	print"The default initial values are:"
	print"6,2,8,1,2,135,90,10"
	print
	input"Do you want these or a random selection ";reply$
	if ucase$(left$(reply$,1)) = "R" then

		randomize timer
		
		biomorphs%(1,1) = int(rnd * 16) + 1
		biomorphs%(1,2) = int(rnd * 8)
		biomorphs%(1,3) = int(rnd * 8) + 1
		biomorphs%(1,4) = int(rnd * 8) + 1
		biomorphs%(1,5) = int(rnd * 2) + 1
		biomorphs%(1,6) = int(rnd * 360) + 1
		biomorphs%(1,7) = int(rnd * 360) + 1
		biomorphs%(1,8) = int(rnd * 50) + 1
		for bio% = 1 to 8
		
			print bio%;": ";biomorphs%(1,bio%)
		
		next bio%

	else

		biomorphs%(1,1) = 6
		biomorphs%(1,2) = 2
		biomorphs%(1,3) = 8
		biomorphs%(1,4) = 1
		biomorphs%(1,5) = 2
		biomorphs%(1,6) = 135
		biomorphs%(1,7) = 90
		biomorphs%(1,8) = 10
		print"Default values used"
	
	end if

end if
print
print"To end at any point, just press RETURN on it's own to the"
print"'Which biomorph do you want ?' prompt."
print

for bio% = 1 to 8
	for popn% = 2 to biomorphs%(1,1)
		biomorphs%(popn%,bio%) = biomorphs%(1,bio%)
	next popn%
next bio%

input"Press RETURN to show this biomorph ";reply$
cls
popn% = 1

call bioplot(posns%(),biomorphs%(),popn%)

locate 1,1
input"Press RETURN to start ";reply$
popn% = biomorphs%(1,1)
cls

do

	call mutate(biomorphs%(),popn%)
	call bioplot(posns%(),biomorphs%(),popn%)
	do
		locate 1,1
                print"                                                               "
                locate 1,1
        	input"Do you want to see any of these alone ";reply$
		if ucase$(left$(reply$,1)) = "Y" then
        		do
        			locate 1,1
        			print"                                                       "
        			locate 1,1
        			input"Which one do you want ";choice%
         		loop until choice% >= 1 and choice% <= popn%
         		cls
        		call bp2(posns%(),biomorphs%(),choice%)
                	locate 1,1
                	print"                                            "
                	locate 1,1
                	input"Press RETURN to continue ";rep$
                	cls
			call bioplot(posns%(),biomorphs%(),popn%)
		end if
	loop until ucase$(left$(reply$,1)) <> "Y"

	call choose(biomorphs%(),popn%)
	popn% = biomorphs%(1,1)
        cls

loop until popn% = 0

end

$INCLUDE"BIOPLOT.INC"
$INCLUDE"VTRPLOT.INC"
$INCLUDE"SELECT.INC"
$INCLUDE"MUTATE.INC"
$INCLUDE"BP2.INC"
