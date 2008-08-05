/************************************************************

Copyright (C) 1998, Lucent Technologies
All rights reserved

************************************************************/

#include "map.h"

#define Xaitwist Xaitpole.nlat
static struct place Xaitpole;

static int
Xaitoff(struct place *place, double *x, double *y)
{
	struct place p;
	copyplace(place,&p);
	p.wlon.l /= 2.;
	trig(&p.wlon);
	norm(&p,&Xaitpole,&Xaitwist);
	Xazequalarea(&p,x,y);
	*x *= 2.;
	return(1);
}

proj
aitoff(void)
{
	latlon(0.,0.,&Xaitpole);
	return(Xaitoff);
}
