#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/* convert an ascii file of lat-lon data to map(5) format,

   input: sequence of segments, each of which comprises
		integer count
		sequence of north-lat west-lon pairs

   first phase (mapfile1.c): make intermediate file
   intermediate data layout, one line per point:
	patchlat (-9 to 8)	10-degree patch in which 
	patchlon (-18 to 17)	    segment starts
	point number		sequential, with gap between segs
	scaled lat		units of .0001 radian (6.4km, 4mi)
	scaled lon		    or .00001 radian (option -f)

   interphase: sort the intermediate file by patch and point number

   second phase (mapfile2.c): convert to map(5) binary

   warning: incomplete error checking.
*/

/* FIRST PHASE */

#define RAD (M_PI/180)
#define SCALE (10000*RAD)
#define BIGSCALE (100000*RAD)
#define NN SHRT_MAX	/* max points/segment */
#define N (NN-1000)	/* same, before interpolation */

int min(int,int);
int max(int,int);
int plat(int);
int plon(int);
int interpolate(int,int);
double round(double);
void output(int);
void warn(char*);
void error(char*);

int point;		/* sequence number */
double lat[N];
double lon[N];
double scale = SCALE;

int main(int argc, char **argv)
{
	int i, j, n;
	int fflag = 0;
	if(argc>1 && strcmp(argv[1],"-f")==0) {
		fflag = 1;
		scale = BIGSCALE;
	}
	while(scanf("%d", &n) == 1) {
		i = 0;
		do {
			int m = min(n,N);
			n -= m;
			for( ; i<m; i++) {
				if(scanf("%lf %lf",lat+i,lon+i) != 2)
					error("input count error");
				if(fabs(lat[i]) > 90)
					error("latitude out of bounds");
				while(lon[i] < -180)
					lon[i] += 360;
				while(lon[i] > 180)
					lon[i] -= 360;
			}
			if(fflag) {
				for(j=0; j<m-1; j++) {
					int d = interpolate(j, m);
					j += d;
					m += d;
				}
			}
			do {
				for(j=2;j<m-1;j++)
					if(plat(j)!=plat(j-1) ||
					   plon(j)!=plon(j-1)) 
					 	break;
				if(m < 3)
					j = m-1;
				output(j+1);
				memmove(lat,lat+j,(m-j)*sizeof(*lat));
				memmove(lon,lon+j,(m-j)*sizeof(*lon));
				m -= j;
			} while(m > 1);
			i = 1;
		} while(n > 1);
	}
	return 0;
}

/* find patch number, counted in 10-degree units */

int plat(int i)
{
	return min(floor(lat[i]/10),8);
}

int plon(int i)
{
	return min(floor(lon[i]/10),17);
}

/* split large steps to fit in a char */

#define DELTA (SCHAR_MAX-1)	/* wiggle room for roundoff */

int interpolate(int j, int n)
{
	int m, mlat, mlon;	/* number of substeps */
	int from, to;
	double dlat, dlon;
	double slat0 = round(lat[j]*scale);
	double slat1 = round(lat[j+1]*scale);
	double slon0 = round(lon[j]*scale);
	double slon1 = round(lon[j+1]*scale);
	int sdlat = abs(slat1-slat0);
	int sdlon = abs(slon1-slon0);
	if(sdlon > 180)
		sdlon -= 360;	/* probably crossed dateline */
	mlat = (sdlat+DELTA-1)/DELTA; 
	mlon = (sdlon+DELTA-1)/DELTA;
	m = max(mlat, mlon) - 1;	/* # of extra points */
	if(m == 0)
		return 0;
	if(m >= 10)
		warn("long segment (> 10 substeps)");
	if(n+m > NN)
		error("too many interpolated points in segment");
	from = j + 1;
	to = j + m;
	memmove(lat+to,lat+from,(n-from)*sizeof(*lat));
	memmove(lon+to,lon+from,(n-from)*sizeof(*lon));
	dlat = lat[j+1] - lat[j];
	dlon = lon[j+1] - lon[j];
	while(j < m) {
		lat[j+1] = lat[j] + dlat;
		lon[j+1] = lon[j] + dlon;
		j++;
	}
	return m;
}

void output(int n)
{
	int i;
	int plat0 = plat(n>1);
	int plon0 = plon(n>1);
	point++;
	for(i=0; i<n; i++) {
		printf("%d %d %d %d %d\n",plat0,plon0,point,
			(int)round(lat[i]*scale),
			(int)round(lon[i]*scale));
		point++;
	}
}

int min(int a, int b)
{
	return a<=b? a: b;
}

int max(int a, int b)
{
	return a>=b? a: b;
}

void warn(char *s) 
{
	fprintf(stderr,"ascii2map: %s\n", s);
}

void error(char *s) 
{
	warn(s);
	exit(1);
}

double round(double x)
{
	if(x >= 0)
		return (int)(x+0.5);
	else
		return (int)(x-0.5);
}
