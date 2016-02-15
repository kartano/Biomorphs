' Subroutine CHOOSE
' This routine is called once the user has seen the biomorphs. The selection
' is done by number and this takes care of the reorganisation of the data.

SUB CHOOSE(biomorphs%(2),popn%)

local reply$,choice%,count1%,count2%

	do
		locate 1,1
		print"                                                                 "
		locate 1,1
		input"Please enter the number of the biomorph you want ";choice%
        loop until choice% <= popn%

if choice% = 0 then
	biomorphs%(1,1) = 0
else
	for count1% = 1 to 16
		for  count2% = 1 to 8
			biomorphs%(count1%,count2%) = biomorphs%(choice%,count2%)
		next count2%
	next count1%
end if

end sub


