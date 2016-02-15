' Subroutine VECTORPLOT
' This routine does the screen plot for each biomorph vector as BIOPLOT
' generates it. Parameters are the vector array (only one part of this is
' used at each call, but as it is passed as a global variable and not
' copied, this does not matter in execution time); the y coordinate of the
' first branch (because each morph has a vertical mirror plane and only one
' side is actually stored, the other side being calculated from the
' reflection of this vector in the plane) and the pointer to the vector
' (in the vector array) being plotted.

SUB VECTORPLOT(posns%(2),reflec%,vctr%)

local x%,y%,x1%

x% = posns%(vctr%,1)-posns%(vctr%,3)*sin(posns%(vctr%,4)/6.28319)
y% = posns%(vctr%,2)+posns%(vctr%,3)*cos(posns%(vctr%,4)/6.28319)

line (posns%(vctr%,1),posns%(vctr%,2))-(x%,y%),15

x% = 2*reflec% - x%
x1% = 2*reflec% - posns%(vctr%,1)

line (x1%,posns%(vctr%,2))-(x%,y%),15

end sub

