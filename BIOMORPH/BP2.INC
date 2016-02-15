
SUB BP2(posns%(2),biomorphs%(2),bio%)

local presntbase%,oldbase%,itn%

	x% = 320
	reflec% = 320
	y% = 125

	locate 1,1
	input"What magnification do you want ";magn
	
	line (x%,y%)-(x%,(y%-(magn * biomorphs%(bio%,8))))
	
	posns%(1,1) = x% : posns%(1,2) = y%
        posns%(1,3) = biomorphs%(bio%,8) * magn
	
	posns%(2,2) = (y%-(magn * biomorphs%(bio%,8))) : posns%(2,1) = x%

	if biomorphs%(bio%,5)/2 = int(biomorphs%(bio%,5)/2) then
		posns%(2,3) = magn * (biomorphs%(bio%,3) + biomorphs%(bio%,4))
	else
		posns%(2,3) = magn * (biomorphs%(bio%,3) * biomorphs%(bio%,4))
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
				posns%(count%,3) = magn*(biomorphs%(bio%,3)+biomorphs%(bio%,4))
			else
				posns%(count%,3) = magn*(biomorphs%(bio%,3)*biomorphs%(bio%,4))
			end if

			posns%(count%,4) = biomorphs%(bio%,6)	
	
			call vectorplot(posns%(),reflec%,count%)
	
			count% = count% + 1
			posns%(count%,1) = xroot%
			posns%(count%,2) = yroot%
			
			if biomorphs%(bio%,5)/2 = int(biomorphs%(bio%,5)/2) then
				posns%(count%,3) = magn*(biomorphs%(bio%,3)+biomorphs%(bio%,4))
			else
				posns%(count%,3) = magn*(biomorphs%(bio%,3)*biomorphs%(bio%,4))
			end if

			posns%(count%,4) = biomorphs%(bio%,7) - biomorphs%(bio%,6)
	
			call vectorplot(posns%(),reflec%,count%)
			
			count% = count%+1
	
		next vector%
	
		oldbase% = presntbase%
	next itn%
	
locate 12,1
print"Biomorph gene values:"
for itn% = 1 to 8
	print itn%;" : ";biomorphs%(bio%,itn%)
next itn%

end sub		