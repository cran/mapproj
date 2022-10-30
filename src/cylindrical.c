/* RSB #include <u.h>
#include <libc.h>*/
#include "map.h"

int
Xcylindrical(struct place *place, double *x, double *y)
{
	if(fabs(place->nlat.l) > 80.*RAD)
		return(-1);
	*x = - place->wlon.l;
	*y = place->nlat.s / place->nlat.c;
	return(1);
}

proj
cylindrical(double dummy1, double dummy2)
{
	return(Xcylindrical);
}
