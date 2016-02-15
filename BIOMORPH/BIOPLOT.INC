' Subroutine BIOPLOT
' This routine plots the biomorphs according to the parameters held in the
' "gene" array, biomorphs%().
' Each one is plotted in turn as a series of vectors, each vector being held
' in the local array POSNS%(). The data is stored as:
' n,0 = x-coordinate of start position
' n,1 = y-coordinate ------- " -------
' n,2 = length of vector
' n,3 = angle of vector from 0 = vertically upwards, in degrees
'
' The array is 2048 elements long to allow 10 iterations, and takes up 16K
' Plotting occurs as follows:
' One iteration is completed from a base "address" of 2^(itn%)-1 until it is
' finished. The next one starts immediately, reading the vector from which
' it comes as the old base address is stored.

SUB BIOPLOT(posns%(2),biomorphs%(2),popn%)

local presntbase%,oldbase%,itn%,bio%

for bio% = 1 to popn%
	
	if bio% < 9 then
                if bio%/2 = int(bio%/2) then
                	y% = 70
                else
			y% = 85
		end if	
		x% = 50+((bio%-1)*80)
	else
		if bio%/2 = int(bio%/2) then
			y% = 150
		else
		        y% = 165
		end if
		x% = 50+((bio%-9)*80)
	end if
	
	reflec% = x%
	
	line (x%,y%)-(x%,(y%-biomorphs%(bio%,8)))
	
	posns%(1,1) = x% : posns%(1,2) = y%
	posns%(1,3) = biomorphs%(bio%,8) : posns%(1,4) = 90
	
	posns%(2,2) = (y%-biomorphs%(bio%,8)) : posns%(2,1) = x%

	if biomorphs%(bio%,5)/2 = int(biomorphs%(bio%,5)/2) then
        	posns%(2,3) = biomorphs%(bio%,3) + biomorphs%(bio%,4)
        else
        	posns%(2,3) = biomorphs%(bio%,3) * biomorphs%(bio%,4)
        end if
	
	posns%(2,4) = biomorphs%(bio%,6)
	presntbase% = 2
	
	call vectorplot(posns%(),reflec%,presntbase%)
	
	oldbase% = 2
	
	for itn% = 1 to biomorphs%(bio%,2)
		presntbase% = 2^itn% + 1
		count% = presntbase%
	
		for vector% = oldbase% to (presntbase%-1)
			xroot% = posns%(vector%,1) - posns%(vector%,3)*sin(posns%(vector%,4)/6.28319)
			yroot% = posns%(vector%,2) + posns%(vector%,3)*cos(posns%(vector%,4)/6.28319)
			posns%(count%,1) = xroot%
			posns%(count%,2) = yroot%

			if biomorphs%(bio%,5)/2 = int(biomorphs%(bio%,5)/2) then
				posns%(count%,3) = biomorphs%(bio%,3) + biomorphs%(bio%,4)
			else
				posns%(count%,3) = biomorphs%(bio%,3) * biomorphs%(bio%,4)
			end if

			posns%(count%,4) = biomorphs%(bio%,6)	
	
			call vectorplot(posns%(),reflec%,count%)
	
			count% = count% + 1
			posns%(count%,1) = xroot%
			posns%(count%,2) = yroot%

			if biomorphs%(bio%,5)/2 = int(biomorphs%(bio%,5)/2) then
				posns%(count%,3) = biomorphs%(bio%,3) + biomorphs%(bio%,4)
			else
				posns%(count%,3) = biomorphs%(bio%,3) * biomorphs%(bio%,4)
			end if

			posns%(count%,4) = biomorphs%(bio%,7) - biomorphs%(bio%,6)
	
			call vectorplot(posns%(),reflec%,count%)
			
			count% = count%+1
	
		next vector%
	
		oldbase% = presntbase%
	next itn%
	
next bio%

end sub		