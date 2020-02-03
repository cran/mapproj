#include <R.h>
/* RSB #include <u.h>
#include <libc.h>*/
#include "map.h"

// CRAN change 2012-12-10
//extern void abort(void);
#define abort() Rf_error("fatal error in mapproj")

/* these routines duplicate names found in map.c.  they are
called from routines in hex.c, guyou.c, and tetra.c, which
are in turn invoked directly from map.c.  this bad organization
arises from data hiding; only these three files know stuff
that's necessary for the proper handling of the unusual cuts
involved in these projections.

the calling routines are not advertised as part of the library,
and the library duplicates should never get loaded, however they
are included to make the libary self-standing.*/

/* A Deckmyn 2020-01-31

int
picut(struct place *g, struct place *og, double *cutlon)
{
	g; og; cutlon;
	abort();
	return 0;
}

int
ckcut(struct place *g1, struct place *g2, double lon)
{
	g1; g2; lon;
	abort();
	return 0;
}
*/

/* RSB double
reduce(double x)
{
	x;
	abort();
	return 0;
}*/

/* minka: from map.c */
double
reduce(double lon)
{
        if(lon>PI)
                lon -= 2*PI;
        else if(lon<-PI)
                lon += 2*PI;
        return(lon);
}

