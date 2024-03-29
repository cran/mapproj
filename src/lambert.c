/************************************************************

Copyright (C) 1998, Lucent Technologies
All rights reserved

************************************************************/

#include "map.h"

static struct coord stdp0, stdp1;
static double k;

static int
Xlambert(struct place *place, double *x, double *y)
{
	double r;
	if(place->nlat.l < -80.*RAD)
		return(-1);
	if(place->nlat.l > 89.*RAD)
		r = 0;	/* slovenly */
	else
		r = stdp0.c*exp(0.5*k*log(
		   (1+stdp0.s)*(1-place->nlat.s)/((1-stdp0.s)*(1+place->nlat.s))));
	if(stdp1.l<0.)
		r = -r;
	*x = - r*sin(k * place->wlon.l);
	*y = - r*cos(k * place->wlon.l);
	return(1);
}

proj
lambert(double par0, double par1)
{
	double temp;
	if(fabs(par0)>fabs(par1)){
		temp = par0;
		par0 = par1;
		par1 = temp;
	}
	deg2rad(par0, &stdp0);
	deg2rad(par1, &stdp1);
	if(fabs(par1+par0)<.1) 
		return(mercator(UNUSED, UNUSED));
	if(fabs(par1)>89.5) {
		if(par0>89.5)
			return(map_perspective(-1., UNUSED));
		else if(par0<-89.5)
			return 0;	/* S pole stereographic */
		else
			return 0;
	}
	if(fabs(par1-par0)<.1)
	  /* series expansion about stdp1.s = stdp0.s */
	  /* thanks to Alex Deckmyn for pointing this out */
	  k = stdp0.s + 0.5*(stdp1.s - stdp0.s);
	else 
	  k = 2*log(stdp1.c/stdp0.c)/log(
		(1+stdp0.s)*(1-stdp1.s)/((1-stdp0.s)*(1+stdp1.s)));
	return(Xlambert);
}
