' Subroutine MUTATE
' This calculates the gene for mutation and the mutation occurring
'
' The routine takes as parameters the array holding the biomorphs, which has
' biomorphs%(x%,y%) where x% is the biomorph & y% is the gene; and popn%,
' the number of biomorphs. This also takes care of limits such as the max.
' no. of offspring (gene 1) being 16 and no value can be < 1


SUB MUTATE(biomorphs%(2),popn%)

local mut.gen,mg%,bio%

randomize timer

for bio%  = 1 to popn%

	mut.gen = rnd
	mg% = int(mut.gen*9)+1
	mut.gen = rnd
	if mut.gen < 0.5 then
		biomorphs%(bio%,mg%) = biomorphs%(bio%,mg%) - 1
		if biomorphs%(bio%,mg%) = 0 then
			biomorphs%(bio%,mg%) = 2
		end if
	else
		biomorphs%(bio%,mg%) = biomorphs%(bio%,mg%) + 1
	end if	
        if biomorphs%(bio%,1) = 17 then biomorphs%(bio%,1) = 16
	if biomorphs%(bio%,2) = 11 then biomorphs%(bio%,2) = 10
	if biomorphs%(bio%,3) = 9 then biomorphs%(bio%,3) = 8
	if biomorphs%(bio%,4) = 9 then biomorphs%(bio%,4) = 8

next bio%

end sub	