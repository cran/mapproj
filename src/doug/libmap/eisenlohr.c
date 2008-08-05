#include "map.h"

int 
Xeisenlohr(struct place *p, double *x, double *y)
{
	double s1 = -sin(p->wlon.l/2);
	double c1 = cos(p->wlon.l/2);
	double s2 = sin(p->nlat.l/2);
	double c2 = cos(p->nlat.l/2);
	double t = s2/(c2+sqrt(2*p->nlat.c)*c1);
	double c = sqrt(2/(1+t*t));
	double q = sqrt(p->nlat.c/2);
	double v = sqrt((c2+q*(c1+s1))/(c2+q*(c1-s1)));
	double vi = 1/v;
	*x = -2*log(v) + c*(v-vi);
	*y = -2*atan(t) + c*t*(v+vi);
	return 1;
}

proj
eisenlohr()
{
	return Xeisenlohr;
}
